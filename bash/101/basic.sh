#!/bin/bash
# chmod u+x basic.sh
# ls -l basic.sh
# ./basic.sh

report_who () {
    echo "The current directory is:" $(pwd)
    echo "The user logged in is:" $(whoami)
    echo "Home for the current user is: $HOME"
return
}

how_to_var () {
    grade=5
    person="Adam"
    mydir=$(pwd)
    var1=$((5 + 5))
    var2=$(($var1 * 2))
    echo "$person is a god boy, he is in grade $grade and his dir $mydir , and var = $var2"
return
}

check_user (){
    user=likegeeks
    
    if grep $user /etc/passwd
        then 
            echo "The user $user Exist"  
    else
    	    echo "The user $user doesn't exist"
    fi
return
}

check_value () {
    vall=6
    
    if [ $vall -gt 5 ]
        then
            echo "The test value $vall is greater than 5"
    else
            echo "The test value $vall is not greater than 5"
    fi
return
}
