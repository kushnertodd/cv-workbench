for f in \
experiment9-prewitt-definition.json \
experiment9-roberts-definition.json \
experiment9-sobel-orientation-0-definition.json  \
experiment9-sobel-orientation-90-definition.json 
do
echo ./parse_experiment_json  ../config/$f
./parse_experiment_json  ../config/$f
done
