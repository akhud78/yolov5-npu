#!/bin/bash
# Batch processing of input images

# Default output directory is /tmp, but it can be overridden by the first argument
output_directory=${1:-/tmp}

# Ensure the output directory exists or create it
mkdir -p "$output_directory"

# List of input images for the program
input_files=(
    "../media/bus.jpg"
    "../media/parking.jpg"
)
model="rk3588/yolov5n.rknn"
suffix="_yolov5n."
# model="rk3588/yolov5m.rknn"
# suffix="_yolov5m."
# model="rk3588/yolov5s.rknn"
# suffix="_yolov5s."
# model="rk3588/yolov5s_relu.rknn"
# suffix="_yolov5s_relu."

# Iterate over each input file
for input_file in "${input_files[@]}"; do
    # Extract the base name and extension of the input file
    base_name=$(basename "$input_file")
    extension="${base_name##*.}"
    
    # Construct the output image path with the suffix added before the extension
    output_file="$output_directory/${base_name%.*}${suffix}$extension"
    
    # Run program
    build/yolov5_npu "$input_file" "$model" "$output_file"
    
    # Check the exit status of the example program
    if [ $? -ne 0 ]; then
        echo "Error: The example program failed for input file $input_file."
        exit 1
    fi
done

echo "All files processed successfully."

