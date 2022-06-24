for f in \
experiment9-prewitt-definition.json \
experiment9-roberts-definition.json \
experiment9-sobel-definition.json 
do
echo ./parse_experiment_json  ../config/$f
./parse_experiment_json  ../config/$f
done
