#!/usr/bin/env python3
"""Report a failed vendor SDK download without extracting or trusting it."""
import hashlib
import json
from pathlib import Path
import urllib.request
import zipfile
import tempfile

HERE = Path(__file__).resolve().parent


def main():
    report = {}
    try:
        lock = json.loads((HERE / 'sdk.lock.json').read_text())
        report['expected_sha256'] = lock['sha256']
        with tempfile.TemporaryDirectory(prefix='am-sdk-probe-') as folder:
            archive = Path(folder) / 'download'
            request = urllib.request.Request(lock['url'], headers={'User-Agent': 'AM-Cloud-Build/0.1'})
            with urllib.request.urlopen(request, timeout=60) as response:
                report['final_url'] = response.url
                report['content_type'] = response.headers.get('Content-Type')
                data = response.read(32 * 1024 * 1024 + 1)
                if len(data) > 32 * 1024 * 1024:
                    raise ValueError('Download exceeds diagnostic size limit.')
                archive.write_bytes(data)
            report['bytes'] = len(data)
            report['sha256'] = hashlib.sha256(data).hexdigest()
            report['first_16_bytes_hex'] = data[:16].hex()
            report['is_zip'] = zipfile.is_zipfile(archive)
            if report['is_zip']:
                with zipfile.ZipFile(archive) as z:
                    if sum(e.file_size for e in z.infolist()) > 256 * 1024 * 1024:
                        raise ValueError('Uncompressed size exceeds diagnostic limit.')
                    report['members'] = [
                        {'path': e.filename, 'bytes': e.file_size,
                         'sha256': hashlib.sha256(z.read(e)).hexdigest()}
                        for e in z.infolist() if not e.is_dir()]
    except Exception as error:
        report['error'] = str(error)
    output = HERE / 'artifacts'
    output.mkdir(exist_ok=True)
    text = json.dumps(report, indent=2)
    (output / 'sdk-download-diagnostic.json').write_text(text + '\n', encoding='utf-8')
    print(text)


if __name__ == '__main__':
    main()
