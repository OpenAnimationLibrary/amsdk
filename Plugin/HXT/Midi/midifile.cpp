#include "StdAfx.h"
#include "midifile.h"

/*
 * Data Types
 */

struct MidiFile {
    int file_format;
    MidiFileDivisionType_t division_type;
    int resolution;
    MidiFileTrack *first_track;
    MidiFileTrack *last_track;
};

struct MidiFileTrack {
    MidiFile *midi_file;
    long end_tick;
    MidiFileTrack *previous_track;
    MidiFileTrack *next_track;
    MidiFileEvent *first_event;
    MidiFileEvent *last_event;
};

struct MidiFileEvent {
    MidiFileTrack *track;
    MidiFileEvent *previous_event;
    MidiFileEvent *next_event;
    long tick;
    MidiFileEventType_t type;

    union {
        struct {
            int channel;
            int note;
            int velocity;
        }
        note_off;

        struct {
            int channel;
            int note;
            int velocity;
        }
        note_on;

        struct {
            int channel;
            int note;
            int amount;
        }
        key_pressure;

        struct {
            int channel;
            int number;
            int value;
        }
        control_change;

        struct {
            int channel;
            int number;
        }
        program_change;

        struct {
            int channel;
            int amount;
        }
        channel_pressure;

        struct {
            int channel;
            int value;
        }
        pitch_wheel;

        struct {
            int data_length;
            unsigned char *data_buffer;
        }
        sysex;

        struct {
            int number;
            int data_length;
            unsigned char *data_buffer;
        }
        meta;
    }
    u;

    int should_be_visited;
};

/*
 * Helpers
 */

/*
static signed short interpret_int16(unsigned char *buffer) {
    return ((signed short)(buffer[0]) << 8) | (signed short)(buffer[1]);
}

static signed short read_int16(FILE *in) {
    unsigned char buffer[2];
    fread(buffer, 1, 2, in);
    return interpret_int16(buffer);
}

static void write_int16(FILE *out, signed short value) {
    unsigned char buffer[2];
    buffer[0] = (unsigned char)((value >> 8) & 0xFF);
    buffer[1] = (unsigned char)(value & 0xFF);
    fwrite(buffer, 1, 2, out);
}
*/
static unsigned short interpret_uint16(const unsigned char *buffer) {
    return (unsigned short)buffer[0] << 8 | (unsigned short)buffer[1];
}

static unsigned short read_uint16(FILE *in) {
    unsigned char buffer[2];
    fread(buffer, 1, 2, in);
    return interpret_uint16(buffer);
}

static void write_uint16(FILE *out, const unsigned short value) {
    unsigned char buffer[2];
    buffer[0] = (unsigned char)(value >> 8 & 0xFF);
    buffer[1] = (unsigned char)(value & 0xFF);
    fwrite(buffer, 1, 2, out);
}

static unsigned long interpret_uint32(const unsigned char *buffer) {
    return (unsigned long)buffer[0] << 24 | (unsigned long)buffer[1] << 16 | (unsigned long)buffer[2] << 8 | (unsigned long)buffer[3];
}

static unsigned long read_uint32(FILE *in) {
    unsigned char buffer[4];
    fread(buffer, 1, 4, in);
    return interpret_uint32(buffer);
}

static void write_uint32(FILE *out, const unsigned long value) {
    unsigned char buffer[4];
    buffer[0] = (unsigned char)(value >> 24);
    buffer[1] = (unsigned char)(value >> 16 & 0xFF);
    buffer[2] = (unsigned char)(value >> 8 & 0xFF);
    buffer[3] = (unsigned char)(value & 0xFF);
    fwrite(buffer, 1, 4, out);
}

static unsigned long read_variable_length_quantity(FILE *in) {
    unsigned char b;
    unsigned long value = 0;

    do {
        b = fgetc(in);
        value = value << 7 | (b & 0x7F);
    } while ((b & 0x80) == 0x80);

    return value;
}

static void write_variable_length_quantity(FILE *out, unsigned long value) {
    unsigned char buffer[4];
    int offset = 3;

    while (true) {
        buffer[offset] = (unsigned char)(value & 0x7F);
        if (offset < 3)
            buffer[offset] |= 0x80;
        value >>= 7;
        if (value == 0 || offset == 0)
            break;
        offset--;
    }

    fwrite(buffer + offset, 1, 4 - offset, out);
}

static int get_number_of_tracks(MidiFile_t midi_file) {
    int number_of_tracks = 0;

    for (MidiFileTrack_t track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track))
        number_of_tracks++;

    return number_of_tracks;
}

static void add_event_to_track(MidiFileTrack_t track, MidiFileEvent_t new_event) {
    /* Add in proper sorted order.  Search backwards to optimize for appending. */

    MidiFileEvent_t midi_event;

    for (midi_event = track->last_event; midi_event != nullptr && new_event->tick < midi_event->tick; midi_event = midi_event->previous_event) {}

    new_event->previous_event = midi_event;

    if (midi_event == nullptr) {
        new_event->next_event = track->first_event;
        track->first_event = new_event;
    } else {
        new_event->next_event = midi_event->next_event;
        midi_event->next_event = new_event;
    }

    if (new_event->next_event == nullptr) {
        track->last_event = new_event;
    } else {
        new_event->next_event->previous_event = new_event;
    }

    if (new_event->tick > track->end_tick)
        track->end_tick = new_event->tick;
}

static void remove_event_from_track(MidiFileTrack_t track, MidiFileEvent_t midi_event) {
    if (midi_event->previous_event == nullptr) {
        track->first_event = midi_event->next_event;
    } else {
        midi_event->previous_event->next_event = midi_event->next_event;
    }

    if (midi_event->next_event == nullptr) {
        track->last_event = midi_event->previous_event;
    } else {
        midi_event->next_event->previous_event = midi_event->previous_event;
    }
}

static void free_events_in_track(MidiFileTrack_t track) {
    MidiFileEvent_t next_event;

    for (MidiFileEvent_t midi_event = track->first_event; midi_event != nullptr; midi_event = next_event) {
        next_event = midi_event->next_event;

        switch (midi_event->type) {
            case MIDI_FILE_EVENT_TYPE_SYSEX:
            {
                free(midi_event->u.sysex.data_buffer);
                break;
            }
            case MIDI_FILE_EVENT_TYPE_META:
            {
                free(midi_event->u.meta.data_buffer);
                break;
            }
            default:
                break;
        }

        free(midi_event);
    }
}

/*
 * Public API
 */

MidiFile_t MidiFile_load(const char *filename) {
    if (filename == nullptr)
        return nullptr;
    FILE *in;

    if (fopen_s(&in ,filename, "rb") != 0)
        return nullptr;
    MidiFile_t midi_file;
    unsigned char chunk_id[4], division_type_and_resolution[4];
    int number_of_tracks_read = 0;
    fread(chunk_id, 1, 4, in);
    long chunk_size = read_uint32(in);
    long chunk_start = ftell(in);

    /* check for the RMID variation on SMF */

    if (memcmp(chunk_id, "RIFF", 4) == 0) {
        fread(chunk_id, 1, 4, in); /* technically this one is a type id rather than a chunk id, but we'll reuse the buffer anyway */

        if (memcmp(chunk_id, "RMID", 4) != 0) {
            fclose(in);
            return nullptr;
        }

        fread(chunk_id, 1, 4, in);
        chunk_size = read_uint32(in);

        if (memcmp(chunk_id, "data", 4) != 0) {
            fclose(in);
            return nullptr;
        }

        fread(chunk_id, 1, 4, in);
        chunk_size = read_uint32(in);
        chunk_start = ftell(in);
    }

    if (memcmp(chunk_id, "MThd", 4) != 0) {
        fclose(in);
        return nullptr;
    }

    const int file_format = read_uint16(in);
    const int number_of_tracks = read_uint16(in);
    fread(division_type_and_resolution, 1, 2, in);

    switch ((signed char)division_type_and_resolution[0]) {
        case -24:
        {
            midi_file = MidiFile_new(file_format, MIDI_FILE_DIVISION_TYPE_SMPTE24, division_type_and_resolution[1]);
            break;
        }
        case -25:
        {
            midi_file = MidiFile_new(file_format, MIDI_FILE_DIVISION_TYPE_SMPTE25, division_type_and_resolution[1]);
            break;
        }
        case -29:
        {
            midi_file = MidiFile_new(file_format, MIDI_FILE_DIVISION_TYPE_SMPTE30DROP, division_type_and_resolution[1]);
            break;
        }
        case -30:
        {
            midi_file = MidiFile_new(file_format, MIDI_FILE_DIVISION_TYPE_SMPTE30, division_type_and_resolution[1]);
            break;
        }
        default:
        {
            midi_file = MidiFile_new(file_format, MIDI_FILE_DIVISION_TYPE_PPQ, interpret_uint16(division_type_and_resolution));
            break;
        }
    }

    /* forwards compatibility:  skip over any extra header data */
    fseek(in, chunk_start + chunk_size, SEEK_SET);

    while (number_of_tracks_read < number_of_tracks) {
        fread(chunk_id, 1, 4, in);
        chunk_size = read_uint32(in);
        chunk_start = ftell(in);

        if (memcmp(chunk_id, "MTrk", 4) == 0) {
            const MidiFileTrack_t track = MidiFile_createTrack(midi_file);
            long previous_tick = 0;
            unsigned char running_status = 0;
            int at_end_of_track = 0;

            while (ftell(in) < chunk_start + chunk_size && !at_end_of_track) {
                const long tick = read_variable_length_quantity(in) + previous_tick;
                previous_tick = tick;

                unsigned char status = fgetc(in);

                if ((status & 0x80) == 0x00) {
                    status = running_status;
                    fseek(in, -1, SEEK_CUR);
                } else {
                    running_status = status;
                }

                switch (status & 0xF0) {
                    case 0x80:
                    {
                        const int channel = status & 0x0F;
                        const int note = fgetc(in);
                        const int velocity = fgetc(in);
                        MidiFileTrack_createNoteOffEvent(track, tick, channel, note, velocity);
                        break;
                    }
                    case 0x90:
                    {
                        const int channel = status & 0x0F;
                        const int note = fgetc(in);
                        const int velocity = fgetc(in);
                        MidiFileTrack_createNoteOnEvent(track, tick, channel, note, velocity);
                        break;
                    }
                    case 0xA0:
                    {
                        const int channel = status & 0x0F;
                        const int note = fgetc(in);
                        const int amount = fgetc(in);
                        MidiFileTrack_createKeyPressureEvent(track, tick, channel, note, amount);
                        break;
                    }
                    case 0xB0:
                    {
                        const int channel = status & 0x0F;
                        const int number = fgetc(in);
                        const int value = fgetc(in);
                        MidiFileTrack_createControlChangeEvent(track, tick, channel, number, value);
                        break;
                    }
                    case 0xC0:
                    {
                        const int channel = status & 0x0F;
                        const int number = fgetc(in);
                        MidiFileTrack_createProgramChangeEvent(track, tick, channel, number);
                        break;
                    }
                    case 0xD0:
                    {
                        const int channel = status & 0x0F;
                        const int amount = fgetc(in);
                        MidiFileTrack_createChannelPressureEvent(track, tick, channel, amount);
                        break;
                    }
                    case 0xE0:
                    {
                        const int channel = status & 0x0F;
                        int value = fgetc(in);
                        value = value << 7 | fgetc(in);
                        MidiFileTrack_createPitchWheelEvent(track, tick, channel, value);
                        break;
                    }
                    case 0xF0:
                    {
                        switch (status) {
                            case 0xF0:
                            case 0xF7:
                            {
                                const int data_length = read_variable_length_quantity(in) + 1;
                                auto *data_buffer = (unsigned char *)malloc(data_length);
                                data_buffer[0] = status;
                                fread(data_buffer + 1, 1, data_length - 1, in);
                                MidiFileTrack_createSysexEvent(track, tick, data_length, data_buffer);
                                free(data_buffer);
                                break;
                            }
                            case 0xFF:
                            {
                                const int number = fgetc(in);
                                const int data_length = read_variable_length_quantity(in);
                                auto *data_buffer = (unsigned char *)malloc(data_length);
                                fread(data_buffer, 1, data_length, in);

                                if (number == 0x2F) {
                                    MidiFileTrack_setEndTick(track, tick);
                                    at_end_of_track = 1;
                                } else {
                                    MidiFileTrack_createMetaEvent(track, tick, number, data_length, data_buffer);
                                }

                                free(data_buffer);
                                break;
                            }
                        }

                        break;
                    }
                }
            }

            number_of_tracks_read++;
        }

        /* forwards compatibility:  skip over any unrecognized chunks, or extra data at the end of tracks */
        fseek(in, chunk_start + chunk_size, SEEK_SET);
    }

    fclose(in);
    return midi_file;
}

int MidiFile_save(MidiFile_t midi_file, const char *filename) {
    if (midi_file == nullptr || filename == nullptr)
        return -1;

    FILE *out;
    if (fopen_s(&out, filename, "wb") != 0)
        return -1;
    fwrite("MThd", 1, 4, out);
    write_uint32(out, 6);
    write_uint16(out, (unsigned short)MidiFile_getFileFormat(midi_file));
    write_uint16(out, (unsigned short)get_number_of_tracks(midi_file));

    switch (MidiFile_getDivisionType(midi_file)) {
        case MIDI_FILE_DIVISION_TYPE_PPQ:
        {
            write_uint16(out, (unsigned short)MidiFile_getResolution(midi_file));
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE24:
        {
            fputc(-24, out);
            fputc(MidiFile_getResolution(midi_file), out);
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE25:
        {
            fputc(-25, out);
            fputc(MidiFile_getResolution(midi_file), out);
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE30DROP:
        {
            fputc(-29, out);
            fputc(MidiFile_getResolution(midi_file), out);
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE30:
        {
            fputc(-30, out);
            fputc(MidiFile_getResolution(midi_file), out);
            break;
        }
        default:
            break;
    }

    for (MidiFileTrack_t track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track)) {

        fwrite("MTrk", 1, 4, out);

        const long track_size_offset = ftell(out);
        write_uint32(out, 0);

        const long track_start_offset = ftell(out);

        long previous_tick = 0;

        for (MidiFileEvent_t midi_event = MidiFileTrack_getFirstEvent(track); midi_event != nullptr; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
            const long tick = MidiFileEvent_getTick(midi_event);
            write_variable_length_quantity(out, tick - previous_tick);

            switch (MidiFileEvent_getType(midi_event)) {
                case MIDI_FILE_EVENT_TYPE_NOTE_OFF:
                {
                    fputc(0x80 | (MidiFileNoteOffEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileNoteOffEvent_getNote(midi_event) & 0x7F, out);
                    fputc(MidiFileNoteOffEvent_getVelocity(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_NOTE_ON:
                {
                    fputc(0x90 | (MidiFileNoteOnEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileNoteOnEvent_getNote(midi_event) & 0x7F, out);
                    fputc(MidiFileNoteOnEvent_getVelocity(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_KEY_PRESSURE:
                {
                    fputc(0xA0 | (MidiFileKeyPressureEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileKeyPressureEvent_getNote(midi_event) & 0x7F, out);
                    fputc(MidiFileKeyPressureEvent_getAmount(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE:
                {
                    fputc(0xB0 | (MidiFileControlChangeEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileControlChangeEvent_getNumber(midi_event) & 0x7F, out);
                    fputc(MidiFileControlChangeEvent_getValue(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE:
                {
                    fputc(0xC0 | (MidiFileProgramChangeEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileProgramChangeEvent_getNumber(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE:
                {
                    fputc(0xD0 | (MidiFileChannelPressureEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(MidiFileChannelPressureEvent_getAmount(midi_event) & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_PITCH_WHEEL:
                {
                    const int value = MidiFilePitchWheelEvent_getValue(midi_event);
                    fputc(0xE0 | (MidiFilePitchWheelEvent_getChannel(midi_event) & 0x0F), out);
                    fputc(value >> 7 & 0x7F, out);
                    fputc(value & 0x7F, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_SYSEX:
                {
                    const int data_length = MidiFileSysexEvent_getDataLength(midi_event);
                    const unsigned char *data = MidiFileSysexEvent_getData(midi_event);
                    fputc(data[0], out);
                    write_variable_length_quantity(out, data_length - 1);
                    fwrite(data + 1, 1, data_length - 1, out);
                    break;
                }
                case MIDI_FILE_EVENT_TYPE_META:
                {
                    const int data_length = MidiFileMetaEvent_getDataLength(midi_event);
                    const unsigned char *data = MidiFileMetaEvent_getData(midi_event);
                    fputc(0xFF, out);
                    fputc(MidiFileMetaEvent_getNumber(midi_event) & 0x7F, out);
                    write_variable_length_quantity(out, data_length);
                    fwrite(data, 1, data_length, out);
                    break;
                }
                default:
                    break;
            }

            previous_tick = tick;
        }

        write_variable_length_quantity(out, MidiFileTrack_getEndTick(track) - previous_tick);
        fwrite("\xFF\x2F\x00", 1, 3, out);

        const long track_end_offset = ftell(out);

        fseek(out, track_size_offset, SEEK_SET);
        write_uint32(out, track_end_offset - track_start_offset);

        fseek(out, track_end_offset, SEEK_SET);
    }

    fclose(out);
    return 0;
}

MidiFile_t MidiFile_new(const int file_format, const MidiFileDivisionType_t division_type, const int resolution) {
    auto *const midi_file = (MidiFile_t)malloc(sizeof(struct MidiFile));
    midi_file->file_format = file_format;
    midi_file->division_type = division_type;
    midi_file->resolution = resolution;
    midi_file->first_track = nullptr;
    midi_file->last_track = nullptr;
    return midi_file;
}

int MidiFile_free(MidiFile_t midi_file) {
    MidiFileTrack_t next_track;

    if (midi_file == nullptr)
        return -1;

    for (MidiFileTrack_t track = midi_file->first_track; track != nullptr; track = next_track) {
        next_track = track->next_track;
        free_events_in_track(track);
        free(track);
    }

    free(midi_file);
    return 0;
}

int MidiFile_getFileFormat(MidiFile_t midi_file) {
    if (midi_file == nullptr)
        return -1;
    return midi_file->file_format;
}

int MidiFile_setFileFormat(MidiFile_t midi_file, const int file_format) {
    if (midi_file == nullptr)
        return -1;
    midi_file->file_format = file_format;
    return 0;
}

MidiFileDivisionType_t MidiFile_getDivisionType(MidiFile_t midi_file) {
    if (midi_file == nullptr)
        return MIDI_FILE_DIVISION_TYPE_INVALID;
    return midi_file->division_type;
}

int MidiFile_setDivisionType(MidiFile_t midi_file, const MidiFileDivisionType_t division_type) {
    if (midi_file == nullptr)
        return -1;
    midi_file->division_type = division_type;
    return 0;
}

int MidiFile_getResolution(MidiFile_t midi_file) {
    if (midi_file == nullptr)
        return -1;
    return midi_file->resolution;
}

int MidiFile_setResolution(MidiFile_t midi_file, const int resolution) {
    if (midi_file == nullptr)
        return -1;
    midi_file->resolution = resolution;
    return 0;
}

MidiFileTrack_t MidiFile_createTrack(MidiFile_t midi_file) {

    if (midi_file == nullptr)
        return nullptr;

    auto *const new_track = (MidiFileTrack_t)malloc(sizeof(struct MidiFileTrack));
    new_track->midi_file = midi_file;
    new_track->end_tick = 0;
    new_track->previous_track = midi_file->last_track;
    new_track->next_track = nullptr;
    midi_file->last_track = new_track;

    if (new_track->previous_track == nullptr) {
        midi_file->first_track = new_track;
    } else {
        new_track->previous_track->next_track = new_track;
    }

    new_track->first_event = nullptr;
    new_track->last_event = nullptr;

    return new_track;
}

MidiFileTrack_t MidiFile_getFirstTrack(MidiFile_t midi_file) {
    if (midi_file == nullptr)
        return nullptr;
    return midi_file->first_track;
}

MidiFileTrack_t MidiFile_getLastTrack(MidiFile_t midi_file) {
    if (midi_file == nullptr)
        return nullptr;
    return midi_file->last_track;
}

int MidiFileTrack_delete(MidiFileTrack_t track) {
    if (track == nullptr)
        return -1;

    if (track->previous_track == nullptr) {
        track->midi_file->first_track = track->next_track;
    } else {
        track->previous_track->next_track = track->next_track;
    }

    if (track->next_track == nullptr) {
        track->midi_file->last_track = track->previous_track;
    } else {
        track->next_track->previous_track = track->previous_track;
    }

    free_events_in_track(track);
    free(track);
    return 0;
}

MidiFile_t MidiFileTrack_getMidiFile(MidiFileTrack_t track) {
    if (track == nullptr)
        return nullptr;
    return track->midi_file;
}

long MidiFileTrack_getEndTick(MidiFileTrack_t track) {
    if (track == nullptr)
        return -1;
    return track->end_tick;
}

int MidiFileTrack_setEndTick(MidiFileTrack_t track, const long end_tick) {
    if (track == nullptr || end_tick < track->end_tick)
        return -1;
    track->end_tick = end_tick;
    return 0;
}

MidiFileTrack_t MidiFileTrack_createTrackBefore(MidiFileTrack_t track) {

    if (track == nullptr)
        return nullptr;

    auto *const new_track = (MidiFileTrack_t)malloc(sizeof(struct MidiFileTrack));
    new_track->midi_file = track->midi_file;
    new_track->end_tick = 0;
    new_track->previous_track = track->previous_track;
    new_track->next_track = track;
    track->previous_track = new_track;

    if (new_track->previous_track == nullptr) {
        track->midi_file->first_track = new_track;
    } else {
        new_track->previous_track->next_track = new_track;
    }

    new_track->first_event = nullptr;
    new_track->last_event = nullptr;

    return new_track;
}

MidiFileTrack_t MidiFileTrack_getPreviousTrack(MidiFileTrack_t track) {
    if (track == nullptr)
        return nullptr;
    return track->previous_track;
}

MidiFileTrack_t MidiFileTrack_getNextTrack(MidiFileTrack_t track) {
    if (track == nullptr)
        return nullptr;
    return track->next_track;
}

MidiFileEvent_t MidiFileTrack_createNoteOffEvent(MidiFileTrack_t track, const long tick, const int channel, const int note, const int velocity) {

    if (track == nullptr)
        return nullptr;
    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_NOTE_OFF;
    new_event->u.note_off.channel = channel;
    new_event->u.note_off.note = note;
    new_event->u.note_off.velocity = velocity;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createNoteOnEvent(MidiFileTrack_t track, const long tick, const int channel, const int note, const int velocity) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_NOTE_ON;
    new_event->u.note_on.channel = channel;
    new_event->u.note_on.note = note;
    new_event->u.note_on.velocity = velocity;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createKeyPressureEvent(MidiFileTrack_t track, const long tick, const int channel, const int note, const int amount) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_KEY_PRESSURE;
    new_event->u.key_pressure.channel = channel;
    new_event->u.key_pressure.note = note;
    new_event->u.key_pressure.amount = amount;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createControlChangeEvent(MidiFileTrack_t track, const long tick, const int channel, const int number, const int value) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE;
    new_event->u.control_change.channel = channel;
    new_event->u.control_change.number = number;
    new_event->u.control_change.value = value;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createProgramChangeEvent(MidiFileTrack_t track, const long tick, const int channel, const int number) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE;
    new_event->u.program_change.channel = channel;
    new_event->u.program_change.number = number;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createChannelPressureEvent(MidiFileTrack_t track, const long tick, const int channel, const int amount) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE;
    new_event->u.channel_pressure.channel = channel;
    new_event->u.channel_pressure.amount = amount;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createPitchWheelEvent(MidiFileTrack_t track, const long tick, const int channel, const int value) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_PITCH_WHEEL;
    new_event->u.pitch_wheel.channel = channel;
    new_event->u.pitch_wheel.value = value;
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createSysexEvent(MidiFileTrack_t track, const long tick, const int data_length, const unsigned char *data_buffer) {

    if (track == nullptr || data_length < 1 || data_buffer == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_SYSEX;
    new_event->u.sysex.data_length = data_length;
    new_event->u.sysex.data_buffer = (unsigned char *)malloc(data_length);
    memcpy(new_event->u.sysex.data_buffer, data_buffer, data_length);
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_createMetaEvent(MidiFileTrack_t track, const long tick, const int number, const int data_length, const unsigned char *data_buffer) {

    if (track == nullptr)
        return nullptr;

    auto *const new_event = (MidiFileEvent_t)malloc(sizeof(struct MidiFileEvent));
    new_event->track = track;
    new_event->tick = tick;
    new_event->type = MIDI_FILE_EVENT_TYPE_META;
    new_event->u.meta.number = number;
    new_event->u.meta.data_length = data_length;
    new_event->u.meta.data_buffer = (unsigned char *)malloc(data_length);
    memcpy(new_event->u.meta.data_buffer, data_buffer, data_length);
    new_event->should_be_visited = 0;
    add_event_to_track(track, new_event);

    return new_event;
}

MidiFileEvent_t MidiFileTrack_getFirstEvent(MidiFileTrack_t track) {
    if (track == nullptr)
        return nullptr;
    return track->first_event;
}

MidiFileEvent_t MidiFileTrack_getLastEvent(MidiFileTrack_t track) {
    if (track == nullptr)
        return nullptr;
    return track->last_event;
}

int MidiFileTrack_visitEvents(MidiFileTrack_t track, const MidiFileEventVisitorCallback_t visitor_callback, void *user_data) {
    MidiFileEvent_t midi_event, next_event;

    if (track == nullptr || visitor_callback == nullptr)
        return -1;

    for (midi_event = MidiFileTrack_getFirstEvent(track); midi_event != nullptr; midi_event = MidiFileEvent_getNextEvent(midi_event))
        midi_event->should_be_visited = 1;

    for (midi_event = MidiFileTrack_getFirstEvent(track); midi_event != nullptr; midi_event = next_event) {
        next_event = MidiFileEvent_getNextEvent(midi_event);

        if (midi_event->should_be_visited) {
            midi_event->should_be_visited = 0;
            (*visitor_callback)(midi_event, user_data);
        }
    }

    return 0;
}

int MidiFileEvent_delete(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return -1;
    remove_event_from_track(midi_event->track, midi_event);

    switch (midi_event->type) {
        case MIDI_FILE_EVENT_TYPE_SYSEX:
        {
            free(midi_event->u.sysex.data_buffer);
            break;
        }
        case MIDI_FILE_EVENT_TYPE_META:
        {
            free(midi_event->u.meta.data_buffer);
            break;
        }
        default: ;
    }

    free(midi_event);
    return 0;
}

MidiFileTrack_t MidiFileEvent_getTrack(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return nullptr;
    return midi_event->track;
}

MidiFileEvent_t MidiFileEvent_getPreviousEvent(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return nullptr;
    return midi_event->previous_event;
}

MidiFileEvent_t MidiFileEvent_getNextEvent(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return nullptr;
    return midi_event->next_event;
}

long MidiFileEvent_getTick(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return -1;
    return midi_event->tick;
}

int MidiFileEvent_setTick(MidiFileEvent_t midi_event, const long tick) {
    if (midi_event == nullptr)
        return -1;
    remove_event_from_track(midi_event->track, midi_event);
    midi_event->tick = tick;
    add_event_to_track(midi_event->track, midi_event);
    return 0;
}

MidiFileEventType_t MidiFileEvent_getType(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr)
        return MIDI_FILE_EVENT_TYPE_INVALID;
    return midi_event->type;
}

int MidiFileNoteOffEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    return midi_event->u.note_off.channel;
}

int MidiFileNoteOffEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    midi_event->u.note_off.channel = channel;
    return 0;
}

int MidiFileNoteOffEvent_getNote(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    return midi_event->u.note_off.note;
}

int MidiFileNoteOffEvent_setNote(MidiFileEvent_t midi_event, const int note) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    midi_event->u.note_off.note = note;
    return 0;
}

int MidiFileNoteOffEvent_getVelocity(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    return midi_event->u.note_off.velocity;
}

int MidiFileNoteOffEvent_setVelocity(MidiFileEvent_t midi_event, const int velocity) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_OFF)
        return -1;
    midi_event->u.note_off.velocity = velocity;
    return 0;
}

int MidiFileNoteOnEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    return midi_event->u.note_on.channel;
}

int MidiFileNoteOnEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    midi_event->u.note_on.channel = channel;
    return 0;
}

int MidiFileNoteOnEvent_getNote(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    return midi_event->u.note_on.note;
}

int MidiFileNoteOnEvent_setNote(MidiFileEvent_t midi_event, const int note) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    midi_event->u.note_on.note = note;
    return 0;
}

int MidiFileNoteOnEvent_getVelocity(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    return midi_event->u.note_on.velocity;
}

int MidiFileNoteOnEvent_setVelocity(MidiFileEvent_t midi_event, const int velocity) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_NOTE_ON)
        return -1;
    midi_event->u.note_on.velocity = velocity;
    return 0;
}

int MidiFileKeyPressureEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    return midi_event->u.key_pressure.channel;
}

int MidiFileKeyPressureEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    midi_event->u.key_pressure.channel = channel;
    return 0;
}

int MidiFileKeyPressureEvent_getNote(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    return midi_event->u.key_pressure.note;
}

int MidiFileKeyPressureEvent_setNote(MidiFileEvent_t midi_event, const int note) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    midi_event->u.key_pressure.note = note;
    return 0;
}

int MidiFileKeyPressureEvent_getAmount(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    return midi_event->u.key_pressure.amount;
}

int MidiFileKeyPressureEvent_setAmount(MidiFileEvent_t midi_event, const int amount) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_KEY_PRESSURE)
        return -1;
    midi_event->u.key_pressure.amount = amount;
    return 0;
}

int MidiFileControlChangeEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    return midi_event->u.control_change.channel;
}

int MidiFileControlChangeEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    midi_event->u.control_change.channel = channel;
    return 0;
}

int MidiFileControlChangeEvent_getNumber(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    return midi_event->u.control_change.number;
}

int MidiFileControlChangeEvent_setNumber(MidiFileEvent_t midi_event, const int number) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    midi_event->u.control_change.number = number;
    return 0;
}

int MidiFileControlChangeEvent_getValue(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    return midi_event->u.control_change.value;
}

int MidiFileControlChangeEvent_setValue(MidiFileEvent_t midi_event, const int value) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE)
        return -1;
    midi_event->u.control_change.value = value;
    return 0;
}

int MidiFileProgramChangeEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE)
        return -1;
    return midi_event->u.program_change.channel;
}

int MidiFileProgramChangeEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE)
        return -1;
    midi_event->u.program_change.channel = channel;
    return 0;
}

int MidiFileProgramChangeEvent_getNumber(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE)
        return -1;
    return midi_event->u.program_change.number;
}

int MidiFileProgramChangeEvent_setNumber(MidiFileEvent_t midi_event, const int number) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE)
        return -1;
    midi_event->u.program_change.number = number;
    return 0;
}

int MidiFileChannelPressureEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE)
        return -1;
    return midi_event->u.channel_pressure.channel;
}

int MidiFileChannelPressureEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE)
        return -1;
    midi_event->u.channel_pressure.channel = channel;
    return 0;
}

int MidiFileChannelPressureEvent_getAmount(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE)
        return -1;
    return midi_event->u.channel_pressure.amount;
}

int MidiFileChannelPressureEvent_setAmount(MidiFileEvent_t midi_event, const int amount) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE)
        return -1;
    midi_event->u.channel_pressure.amount = amount;
    return 0;
}

int MidiFilePitchWheelEvent_getChannel(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PITCH_WHEEL)
        return -1;
    return midi_event->u.pitch_wheel.channel;
}

int MidiFilePitchWheelEvent_setChannel(MidiFileEvent_t midi_event, const int channel) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PITCH_WHEEL)
        return -1;
    midi_event->u.pitch_wheel.channel = channel;
    return 0;
}

int MidiFilePitchWheelEvent_getValue(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PITCH_WHEEL)
        return -1;
    return midi_event->u.pitch_wheel.value;
}

int MidiFilePitchWheelEvent_setValue(MidiFileEvent_t midi_event, const int value) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_PITCH_WHEEL)
        return -1;
    midi_event->u.pitch_wheel.value = value;
    return 0;
}

int MidiFileSysexEvent_getDataLength(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_SYSEX)
        return -1;
    return midi_event->u.sysex.data_length;
}

unsigned char *MidiFileSysexEvent_getData(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_SYSEX)
        return nullptr;
    return midi_event->u.sysex.data_buffer;
}

int MidiFileSysexEvent_setData(MidiFileEvent_t midi_event, const int data_length, const unsigned char *data_buffer) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_SYSEX || data_length < 1 || data_buffer == nullptr)
        return -1;
    free(midi_event->u.sysex.data_buffer);
    midi_event->u.sysex.data_length = data_length;
    midi_event->u.sysex.data_buffer = (unsigned char *)malloc(data_length);
    memcpy(midi_event->u.sysex.data_buffer, data_buffer, data_length);
    return 0;
}

int MidiFileMetaEvent_getNumber(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_META)
        return -1;
    return midi_event->u.meta.number;
}

int MidiFileMetaEvent_setNumber(MidiFileEvent_t midi_event, const int number) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_META)
        return -1;
    midi_event->u.meta.number = number;
    return 0;
}

int MidiFileMetaEvent_getDataLength(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_META)
        return -1;
    return midi_event->u.meta.data_length;
}

unsigned char *MidiFileMetaEvent_getData(MidiFileEvent_t midi_event) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_META)
        return nullptr;
    return midi_event->u.meta.data_buffer;
}

int MidiFileMetaEvent_setData(MidiFileEvent_t midi_event, const int data_length, const unsigned char *data_buffer) {
    if (midi_event == nullptr || midi_event->type != MIDI_FILE_EVENT_TYPE_META || data_length < 1 || data_buffer == nullptr)
        return -1;
    free(midi_event->u.meta.data_buffer);
    midi_event->u.meta.data_length = data_length;
    midi_event->u.meta.data_buffer = (unsigned char *)malloc(data_length);
    memcpy(midi_event->u.meta.data_buffer, data_buffer, data_length);
    return 0;
}
