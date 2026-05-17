#!/bin/bash
tr -s '\233' '\n' < $1 > $1.new
NEW_NAME=$(echo $1 | tr '[:upper:]' '[:lower:]')
mv $1 $1.old
mv $1.new $NEW_NAME


