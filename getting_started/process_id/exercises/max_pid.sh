#!/bin/bash

# Get maximum value a process id can be.

value=$(cat /proc/sys/kernel/pid_max)

echo "The maximum value a process id can be is $value"
