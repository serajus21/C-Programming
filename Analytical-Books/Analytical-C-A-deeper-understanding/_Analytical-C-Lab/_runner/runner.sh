#!/usr/bin/env bash
# Analytical C lab runner (runs on the reader's Fedora, started by systemd).
# Claude places job scripts in queue/; each is run once with bash, from the
# _Analytical-C-Lab folder, and its combined output is written to done/.
# A job never deletes anything; the runner only moves the job file.
set -u
R="$(cd "$(dirname "$0")" && pwd)"
LAB="$(dirname "$R")"
Q="$R/queue"; W="$R/running"; D="$R/done"
mkdir -p "$Q" "$W" "$D"
shopt -s nullglob
while :; do
  jobs=("$Q"/*.sh)
  [ ${#jobs[@]} -eq 0 ] && break
  for job in "${jobs[@]}"; do
    name="$(basename "$job" .sh)"
    mv -f "$job" "$W/$name.sh" || continue
    {
      echo "job: $name"
      echo "started: $(date -Is)"
      echo "host: $(hostname)"
      echo "os: $(. /etc/os-release; echo "$PRETTY_NAME")"
    } > "$D/$name.meta"
    ( cd "$LAB" && timeout 900 bash "$W/$name.sh" ) > "$D/$name.out" 2>&1
    rc=$?
    mv -f "$W/$name.sh" "$D/$name.sh"
    { echo "finished: $(date -Is)"; echo "exit: $rc"; } >> "$D/$name.meta"
  done
done
