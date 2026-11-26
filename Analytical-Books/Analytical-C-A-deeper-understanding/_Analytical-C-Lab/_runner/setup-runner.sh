#!/usr/bin/env bash
# One-time setup on the reader's Fedora 44 for the Analytical C lab runner.
# Run it once:   bash <path-to-this-file>
# To stop the runner later:  systemctl --user disable --now analytical-c-lab.path
set -eu
R="$(cd "$(dirname "$0")" && pwd)"
echo "== 1. Tools used by Chapter 03 onward (asks for your password once) =="
sudo dnf install -y --skip-unavailable \
  gcc binutils glibc-static glibc-devel gdb strace ltrace file \
  avr-gcc avr-libc avr-binutils simavr elfutils clang || echo "dnf step reported a problem; continuing"
echo "== 2. systemd user units that watch the queue folder =="
U="$HOME/.config/systemd/user"; mkdir -p "$U"
cat > "$U/analytical-c-lab.path" <<UNIT
[Unit]
Description=Watch the Analytical C lab queue

[Path]
DirectoryNotEmpty=$R/queue
MakeDirectory=yes

[Install]
WantedBy=default.target
UNIT
cat > "$U/analytical-c-lab.service" <<UNIT
[Unit]
Description=Run queued Analytical C lab jobs

[Service]
Type=oneshot
ExecStart=/usr/bin/bash $R/runner.sh
UNIT
systemctl --user daemon-reload
systemctl --user enable --now analytical-c-lab.path
echo "== 3. Status =="
systemctl --user --no-pager status analytical-c-lab.path | head -5
echo
echo "Setup finished. Claude can now run lab jobs on this Fedora."
