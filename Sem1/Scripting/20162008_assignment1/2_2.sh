ls -l | grep -E -v "total.[0-9]*$" | tr -s " " | cut -d" " -f2 | sort -nu
