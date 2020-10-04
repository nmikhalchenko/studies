#!/bin/bash

SUBDIR_COUNT=$(($1 + 0))
VARIANT=5

DIRS=$(ls */ -d | cut -d'/' -f 1)
ARRAY=(${DIRS})
NUM=$((${#ARRAY[@]} + 1))

NEWNAME=$(echo ${ARRAY[0]:0:-1}$NUM)

echo "Creating directory ${NEWNAME}..."
mkdir ${NEWNAME}

if [ ${SUBDIR_COUNT} -gt 0 ]
    then
        for i in $(seq 1 ${SUBDIR_COUNT})
        do
            NEWSUB=$(echo ${NEWNAME}/excercise_${i})
            
            echo "Creating subdirectory ${NEWSUB}..."
            mkdir ${NEWSUB}

            echo '#!/bin/bash

gcc ./*c -lm -o output.out' > ${NEWSUB}/build.bash

            chmod a+x ${NEWSUB}/build.bash

            echo "//Вариант ${VARIANT}" > ${NEWSUB}/main.c
            echo '
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    return 0;
}' >> ${NEWSUB}/main.c
        done
fi

echo "Done!"