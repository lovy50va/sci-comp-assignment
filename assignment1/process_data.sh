#!/bin/bash

# ========================================
# Exercise 1: FMB (1a-d) - 13 points
# Scientific Computing I - Assignment 1
# ========================================

echo "Starting data processing pipeline..."

# --- 1a) Script Setup and Unpacking (2 points) ---
if [ ! -f "solver_output.tar.gz" ]; then
    echo "ERROR: solver_output.tar.gz not found!"
    exit 1
fi

inner_file=$(tar -tf solver_output.tar.gz | head -n 1)
tar -xzf solver_output.tar.gz
mv "$inner_file" solver_output.txt
echo "1a) Extracted and renamed to solver_output.txt"

# --- 1b) Data Cleaning and Archiving (5 points) ---
grep -vE '^(-+|\s*it\s*\|)' solver_output.txt | \
sed 's/\s*|\s*/,/g; s/^\s*//; s/\s*$//' > solver_data.csv
echo "1b) Cleaned data saved to solver_data.csv"

tar -czf processed_outputs.tar.gz solver_output.txt solver_data.csv
echo "1b) Archived to processed_outputs.tar.gz"

# --- 1c) Data Validation with Grep and Regex (4 points) ---
grep -E ',[0-9.e+-]+e\+[0-9]+$' solver_data.csv | \
sed -E 's/^([0-9]+),.*,.*,([0-9.e+-]+)$/Warning: High residual change at iteration \1./' \
> instability_report.txt
echo "1c) Instability warnings saved to instability_report.txt"

# --- 1d) Advanced Data Transformation (2 points) ---
echo "solver_data = [" > load_data.m
awk -F, '{printf "%s %s %s %s;\n", $1, $2, $3, $4}' solver_data.csv >> load_data.m
echo "];" >> load_data.m
echo "1d) MATLAB script generated: load_data.m"

echo "All tasks completed successfully!"