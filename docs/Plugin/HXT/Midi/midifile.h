#ifndef MIDI_FILE_INCLUDED
#define MIDI_FILE_INCLUDED

/*
 * Div's Standard MIDI File API
 * Copyright 2003 by David G. Slomin
 * Provided under the terms of the GNU LGPL
 *
 * Usage notes:
 *
 * 1.  Running status is eliminated from messages at load time; it should not
 *     be used at any other time.
 *
 * 2.  MIDI files in formats 0, 1, and 2 are supported, but the caller is
 *     responsible for placing events into the appropriate tracks.  Format
 *     0 files should only use a single track.  Format 1 files use their
 *     first track as a "conductor track" for meta events like tempo and 
 *     meter changes.
 *
 * 3.  MidiFileTrack_visitEvents() is specially designed so that you can add,
 *     delete, or change the tick of events (thereby modifying the sorting
 *     order) without upsetting the iterator.
 *
 * 4.  Any data passed into these functions is memory-managed by the caller.
 *     Any data returned from these functions is memory-managed by the API.
 *     Don't forget to call MidiFile_free().
 *
 * 5.  This API is not thread-safe.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MidiFile *MidiFile_t;
typedef struct MidiFileTrack *MidiFileTrack_t;
typedef struct MidiFileEvent *MidiFileEvent_t;
typedef void (*MidiFileEventVisitorCallback_t)(MidiFileEvent_t midi_event, void *user_data);

typedef enum {
    MIDI_FILE_DIVISION_TYPE_INVALID = -1,
    MIDI_FILE_DIVISION_TYPE_PPQ,
    MIDI_FILE_DIVISION_TYPE_SMPTE24,
    MIDI_FILE_DIVISION_TYPE_SMPTE25,
    MIDI_FILE_DIVISION_TYPE_SMPTE30DROP,
    MIDI_FILE_DIVISION_TYPE_SMPTE30
}
MidiFileDivisionType_t;

typedef enum {
    MIDI_FILE_EVENT_TYPE_INVALID = -1,
    MIDI_FILE_EVENT_TYPE_NOTE_OFF,
    MIDI_FILE_EVENT_TYPE_NOTE_ON,
    MIDI_FILE_EVENT_TYPE_KEY_PRESSURE,
    MIDI_FILE_EVENT_TYPE_CONTROL_CHANGE,
    MIDI_FILE_EVENT_TYPE_PROGRAM_CHANGE,
    MIDI_FILE_EVENT_TYPE_CHANNEL_PRESSURE,
    MIDI_FILE_EVENT_TYPE_PITCH_WHEEL,
    MIDI_FILE_EVENT_TYPE_SYSEX,
    MIDI_FILE_EVENT_TYPE_META
}
MidiFileEventType_t;

MidiFile_t MidiFile_load(const char *filename);
int MidiFile_save(MidiFile_t midi_file, const char *filename);

MidiFile_t MidiFile_new(int file_format, MidiFileDivisionType_t division_type, int resolution);
int MidiFile_free(MidiFile_t midi_file);
int MidiFile_getFileFormat(MidiFile_t midi_file);
int MidiFile_setFileFormat(MidiFile_t midi_file, int file_format);
MidiFileDivisionType_t MidiFile_getDivisionType(MidiFile_t midi_file);
int MidiFile_setDivisionType(MidiFile_t midi_file, MidiFileDivisionType_t division_type);
int MidiFile_getResolution(MidiFile_t midi_file);
int MidiFile_setResolution(MidiFile_t midi_file, int resolution);
MidiFileTrack_t MidiFile_createTrack(MidiFile_t midi_file);
MidiFileTrack_t MidiFile_getFirstTrack(MidiFile_t midi_file);
MidiFileTrack_t MidiFile_getLastTrack(MidiFile_t midi_file);

int MidiFileTrack_delete(MidiFileTrack_t track);
MidiFile_t MidiFileTrack_getMidiFile(MidiFileTrack_t track);
long MidiFileTrack_getEndTick(MidiFileTrack_t track);
int MidiFileTrack_setEndTick(MidiFileTrack_t track, long end_tick);
MidiFileTrack_t MidiFileTrack_createTrackBefore(MidiFileTrack_t track);
MidiFileTrack_t MidiFileTrack_getPreviousTrack(MidiFileTrack_t track);
MidiFileTrack_t MidiFileTrack_getNextTrack(MidiFileTrack_t track);
MidiFileEvent_t MidiFileTrack_createNoteOffEvent(MidiFileTrack_t track, long tick, int channel, int note, int velocity);
MidiFileEvent_t MidiFileTrack_createNoteOnEvent(MidiFileTrack_t track, long tick, int channel, int note, int velocity);
MidiFileEvent_t MidiFileTrack_createKeyPressureEvent(MidiFileTrack_t track, long tick, int channel, int note, int amount);
MidiFileEvent_t MidiFileTrack_createControlChangeEvent(MidiFileTrack_t track, long tick, int channel, int number, int value);
MidiFileEvent_t MidiFileTrack_createProgramChangeEvent(MidiFileTrack_t track, long tick, int channel, int number);
MidiFileEvent_t MidiFileTrack_createChannelPressureEvent(MidiFileTrack_t track, long tick, int channel, int amount);
MidiFileEvent_t MidiFileTrack_createPitchWheelEvent(MidiFileTrack_t track, long tick, int channel, int value);
MidiFileEvent_t MidiFileTrack_createSysexEvent(MidiFileTrack_t track, long tick, int data_length, const unsigned char *data_buffer);
MidiFileEvent_t MidiFileTrack_createMetaEvent(MidiFileTrack_t track, long tick, int number, int data_length, const unsigned char *data_buffer);
MidiFileEvent_t MidiFileTrack_getFirstEvent(MidiFileTrack_t track);
MidiFileEvent_t MidiFileTrack_getLastEvent(MidiFileTrack_t track);
int MidiFileTrack_visitEvents(MidiFileTrack_t track, MidiFileEventVisitorCallback_t visitor_callback, void *user_data);

int MidiFileEvent_delete(MidiFileEvent_t midi_event);
MidiFileTrack_t MidiFileEvent_getTrack(MidiFileEvent_t midi_event);
MidiFileEvent_t MidiFileEvent_getPreviousEvent(MidiFileEvent_t midi_event);
MidiFileEvent_t MidiFileEvent_getNextEvent(MidiFileEvent_t midi_event);
long MidiFileEvent_getTick(MidiFileEvent_t midi_event);
int MidiFileEvent_setTick(MidiFileEvent_t midi_event, long tick);
MidiFileEventType_t MidiFileEvent_getType(MidiFileEvent_t midi_event);

int MidiFileNoteOffEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileNoteOffEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileNoteOffEvent_getNote(MidiFileEvent_t midi_event);
int MidiFileNoteOffEvent_setNote(MidiFileEvent_t midi_event, int note);
int MidiFileNoteOffEvent_getVelocity(MidiFileEvent_t midi_event);
int MidiFileNoteOffEvent_setVelocity(MidiFileEvent_t midi_event, int velocity);

int MidiFileNoteOnEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileNoteOnEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileNoteOnEvent_getNote(MidiFileEvent_t midi_event);
int MidiFileNoteOnEvent_setNote(MidiFileEvent_t midi_event, int note);
int MidiFileNoteOnEvent_getVelocity(MidiFileEvent_t midi_event);
int MidiFileNoteOnEvent_setVelocity(MidiFileEvent_t midi_event, int velocity);

int MidiFileKeyPressureEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileKeyPressureEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileKeyPressureEvent_getNote(MidiFileEvent_t midi_event);
int MidiFileKeyPressureEvent_setNote(MidiFileEvent_t midi_event, int note);
int MidiFileKeyPressureEvent_getAmount(MidiFileEvent_t midi_event);
int MidiFileKeyPressureEvent_setAmount(MidiFileEvent_t midi_event, int amount);

int MidiFileControlChangeEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileControlChangeEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileControlChangeEvent_getNumber(MidiFileEvent_t midi_event);
int MidiFileControlChangeEvent_setNumber(MidiFileEvent_t midi_event, int number);
int MidiFileControlChangeEvent_getValue(MidiFileEvent_t midi_event);
int MidiFileControlChangeEvent_setValue(MidiFileEvent_t midi_event, int value);

int MidiFileProgramChangeEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileProgramChangeEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileProgramChangeEvent_getNumber(MidiFileEvent_t midi_event);
int MidiFileProgramChangeEvent_setNumber(MidiFileEvent_t midi_event, int number);

int MidiFileChannelPressureEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFileChannelPressureEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFileChannelPressureEvent_getAmount(MidiFileEvent_t midi_event);
int MidiFileChannelPressureEvent_setAmount(MidiFileEvent_t midi_event, int amount);

int MidiFilePitchWheelEvent_getChannel(MidiFileEvent_t midi_event);
int MidiFilePitchWheelEvent_setChannel(MidiFileEvent_t midi_event, int channel);
int MidiFilePitchWheelEvent_getValue(MidiFileEvent_t midi_event);
int MidiFilePitchWheelEvent_setValue(MidiFileEvent_t midi_event, int value);

int MidiFileSysexEvent_getDataLength(MidiFileEvent_t midi_event);
unsigned char *MidiFileSysexEvent_getData(MidiFileEvent_t midi_event);
int MidiFileSysexEvent_setData(MidiFileEvent_t midi_event, int data_length, const unsigned char *data_buffer);

int MidiFileMetaEvent_getNumber(MidiFileEvent_t midi_event);
int MidiFileMetaEvent_setNumber(MidiFileEvent_t midi_event, int number);
int MidiFileMetaEvent_getDataLength(MidiFileEvent_t midi_event);
unsigned char *MidiFileMetaEvent_getData(MidiFileEvent_t midi_event);
int MidiFileMetaEvent_setData(MidiFileEvent_t midi_event, int data_length, const unsigned char *data_buffer);

#ifdef __cplusplus
}
#endif

#endif
