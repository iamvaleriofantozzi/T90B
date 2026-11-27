#!/bin/sh
set -eu

repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
flasher="$repo_dir/firmware/tools/flash_atk.py"
package="$repo_dir/firmware/build/temp-test/t90b.atk"

case "${1:-}" in
    --help|-h)
        printf 'Uso: %s [--info]
Firmware: %s
' "$0" "$package"
        exit 0
        ;;
    --info)
        [ "$#" -eq 1 ] || exit 2
        exec uv run --with hidapi python3 "$flasher" --info
        ;;
esac
if [ "$#" -ne 0 ]; then
    printf 'Uso: %s [--info]
' "$0" >&2
    exit 2
fi
if [ ! -s "$package" ]; then
    printf 'Firmware mancante: %s
' "$package" >&2
    exit 1
fi
exec uv run --with hidapi python3 "$flasher" --flash "$package" --yes
