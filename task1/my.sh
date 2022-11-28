#!/bin/bash
if  [ $# -eq 0 ];
then
        echo "param loss"
        exit
else
        str_insert="#time#-`date +%Y-%m-%d-%H-%M-%S`"
        #echo "handle date $str_insert"
        for filename in $1/*
        do
                if [ -f $filename ];
                then
                        if [[ $filename == *#time#* ]]
                        then
                                #echo "1"
                                newfile=`echo $filename | sed "s/#time#.*/${str_insert}/g"`
                                #echo $newfile
                                mv $filename $newfile #`echo $filename | sed 's/#time#.*/$str_insert/g'`
                        else
                                #echo "2"
                                mv $filename "$filename-$str_insert"
                        fi
                fi
        done
        echo "finish"
fi
