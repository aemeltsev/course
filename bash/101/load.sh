#!/bin/bash
# chmod u+x load.sh
# ls -l load.sh
# use ./load.sh -f out.txt 

PROGNAME="$(basename $0)"
TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

report_dmesg () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(sudo dmesg)</pre>
_EOF_
    return
}

report_load () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(cat /var/log/dmesg)</pre>
_EOF_
    return
}

report_boot () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(ls /boot)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat /boot/grub/grub.cfg)</pre>
_EOF_

    return
}

usage () {
    echo "$PROGNAME: usage: $PROGNAME [-f file | -i]"
    return
}

write_out_page () {
    cat <<-_EOF_
    <html>
        <head>
            <title>$TITLE</title>
        </head>
        <body>
            <h1>$TITLE</h1>
            <p>$TIME_STAMP</p>
            $(echo "**************** For report dmesg ****************")
            $(report_dmesg)
            $(echo "**************** For report load ****************")
            $(report_load)
            $(echo "**************** For report boot ****************")
            $(report_boot)
        </body>
    </html>
    
_EOF_
return
}

# handling command line options

interactive=
filename=
while [[ -n "$1" ]]; do
    case "$1" in
        -f | --file)          shift
                              filename="$1"
                              ;;
        -i | --interactive)   interactive=1
                              ;;
        -h | --help)          usage
                              exit
                              ;;
        *)                    usage >&2
                              exit 1
                              ;;
    esac
    shift
done

# interactive mode

if [[ -n "$interactive" ]]; then
    while true; do
        read -p "Enter name of output file: " filename
        if [[ -e "$filename" ]]; then
            read -p "'$filename' exists. Overwrite? [y/n/q] > "
            case "$REPLY" in
                Y|y)    break
                        ;;
                Q|q)    echo "Program terminated."
                        exit
                        ;;
                *)      continue
                        ;;
            esac
        fi
    done
fi

# output html page

if [[ -n "$filename" ]]; then
    if touch "$filename" && [[ -f "$filename" ]]; then
        write_out_page > "$filename"
    else
        echo "$PROGNAME: Cannot write file '$filename'" >&2
        exit 1
    fi
else
    write_out_page
fi