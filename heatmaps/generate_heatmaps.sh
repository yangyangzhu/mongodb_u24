#!/bin/bash

./heatmapMask $1 $2 $3 $4/result
if $? -ne 0;
    exit -1 
fi
zip $5 $4/result/*
