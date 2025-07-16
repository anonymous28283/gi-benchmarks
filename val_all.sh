#!/bin/bash

for dir in */ ; do
    name="${dir%/}"
    echo "Validating $name..."
    bash val.sh "$name"
    status=$?

    if [ $status -ne 0 ]; then
        echo "Validation failed for $name with status $status."
        echo "Press any key to continue, or 'q' to quit."
        read -n 1 -s input
        if [ "$input" = "q" ]; then
            echo -e "\nExiting."
            exit 1
        fi
        echo -e "\nContinuing..."
    fi
done

echo "All validations completed."