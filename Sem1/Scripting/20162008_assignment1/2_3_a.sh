ls -l */*/* | grep -E "^-.*/.*/.*" |tr -s " " | cut -d" " -f9 | sed 's/^/.\//g'
