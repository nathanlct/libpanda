#!/bin/bash

# Author: Jonathan Sprinkle, Jonathan Lee
# Based on example by Rahul Bhadani for the live viewer
# 
# format:
# 
# example:
# 

BASEURL="http://ransom.isis.vanderbilt.edu/GPS_REST_API/rest.php?circles"

VIN_FILE="/etc/libpanda.d/vin"
SPEEDPLANNER_FILE="/etc/libpanda.d/speed_planner.json"

while true;
do
	sleep 13
	
	# TODO: replace with real string once file is created/generated correctly
	PLANNER_STRING=$(echo "test_url" | head)
	
	FULL_COMMAND="curl --connect-timeout 10 -k ${BASEURL}"
	echo "Performing command: ${FULL_COMMAND}"
	$(${FULL_COMMAND} > ${SPEEDPLANNER_FILE})

	# now that we have a new file, re-calculate our speed
	/usr/local/sbin/publish-speed-plan.py
	
done
