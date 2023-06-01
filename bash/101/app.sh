#!/bin/bash
# chmod u+x app.sh
# ls -l app.sh
# ./app.sh

TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

report_dev () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /dev)</pre>
_EOF_
    return
}

report_sys () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /sys)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /sys/block)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /sys/bus)</pre>
_EOF_
    return
}

report_proc () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /proc)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat /proc/cpuinfo)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat  /proc/mounts)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(ls -l /proc/sys)</pre>     
_EOF_
    return
}

report_mod () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(lsmod)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(lspci)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(lsusb)</pre>   
_EOF_
    return
}

report_irq () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(cat /proc/interrupts)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat /proc/ioports)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat /proc/iomem)</pre>
            <pre>$(echo "****************")</pre>
            <pre>$(cat /proc/dma)</pre>
_EOF_
    return
}

report_devices () {
    cat <<-_EOF_
            <pre>$(echo "****************")</pre>
            <pre>$(blkid)</pre>
_EOF_
    return
}

echo "<html>
       <head>
               <title>$TITLE</title>
       </head>
       <body>
           <h1>$TITLE</h1>
           <p>$TIME_STAMP</p>
           $(echo "**************** For /dev ****************")
           $(report_dev)
           $(echo "**************** For /sys ****************")
           $(report_sys)
           $(echo "**************** For /proc ****************")
           $(report_proc)
           $(echo "**************** For module ****************")
           $(report_mod)
           $(echo "**************** For irq io dma ****************")
           $(report_irq)
           $(echo "**************** For udev devices ****************")
           $(report_devices)
        </body>
</html>"