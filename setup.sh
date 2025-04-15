#!/bin/bash
# FPGA Router Project Setup Script

# Function to download and extract a file
download_and_extract() {
    local url=$1
    local output_file=$2
    local extract_dir=$3
    
    echo "Downloading from $url..."
    curl -L -o "$output_file" "$url"
    
    if [ $? -ne 0 ]; then
        echo "Failed to download from $url"
        return 1
    fi
    
    if [[ "$extract_dir" == "." ]]; then
        echo "Extracting $output_file to current directory..."
    else
        echo "Extracting $output_file to $extract_dir folder..."
        mkdir -p "$extract_dir"
    fi
    
    # Determine file type and extract accordingly
    if [[ "$output_file" == *.zip ]]; then
        unzip -o "$output_file" -d "$extract_dir"
    elif [[ "$output_file" == *.tar.gz || "$output_file" == *.tgz ]]; then
        tar -xzf "$output_file" -C "$extract_dir"
    elif [[ "$output_file" == *.tar.bz2 ]]; then
        tar -xjf "$output_file" -C "$extract_dir"
    elif [[ "$output_file" == *.tar ]]; then
        tar -xf "$output_file" -C "$extract_dir"
    else
        echo "Unknown file format for $output_file"
        return 1
    fi
    
    if [ $? -ne 0 ]; then
        echo "Failed to extract $output_file"
        return 1
    fi
    
    echo "Successfully downloaded and extracted $output_file"
    echo "Cleaning up downloaded files..."
    rm "$output_file"

    return 0
}

echo "******************************************************"
echo "*  Executing setup script, this may take a while...  *"
echo "*   DO NOT MODIFY FILES UNTIL THE SCRIPT FINISHES.   *"
echo "******************************************************"
echo

echo "******************************************************"
echo "Downloading benchmarks & device files..."
echo "******************************************************"
echo

download_and_extract "https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/benchmarks.tar.bz2" "benchmarks.tar.bz2" "."
download_and_extract "https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/xcvu3p.tar.bz2" "xcvu3p.tar.bz2" "device"

echo "******************************************************"
echo "Downloading evaluator..."
echo "******************************************************"
echo

curl -L -o eval https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/eval
chmod +x eval

echo "******************************************************"
echo "*                  Setup finished.                   *"
echo "******************************************************"