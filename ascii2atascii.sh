#!/bin/bash
tr -s '\n' '\233' < $1 | sed 's/\t/    /g' > $1.new
NEW_NAME=$(echo $1 | tr '[:lower:]' '[:upper:]')
mv $1 $1.old
mv $1.new $NEW_NAME


