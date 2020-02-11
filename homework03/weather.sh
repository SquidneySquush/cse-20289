 #!/bin/sh

 # Globals
URL="https://forecast.weather.gov/sipcity.php"
ZIPCODE=46556
forecast="NA"
CELSIUS=0

# Functions

usage() {
  cat 1>&2 <<EOF
  Usage: $(basename $0) [zipcode]

  -c    Use Celsius degrees instead of Fahrenheit for temperature
  -f    Display forecast text

  If zipcode is not provided, then it defaults to $ZIPCODE.
EOF
      exit $1
}
weather_information() {
    # Fetch weather information from URL based on ZIPCODE
    curl -sL https://forecast.weather.gov/zipcity.php?inputstring=$ZIPCODE
}

temperature() {
    # Extract temperature information from weather source
    if [ $CELSIUS -eq 1 ]; then
    weather_information | grep "myforecast-current-sm" | grep -Eo "[[:digit:]]+"
    else
    weather_information | grep "myforecast-current-lrg" | grep -Eo "[[:digit:]]+"
    fi
}

forecast() {
    # Extract forecast information from weather source
    weather_information | grep "myforecast-current" | grep -Eo "[[:blank:]],[[:word:]]"| sed -e 's/^\s*//' | sed 's/<p class="myforecast-current">//' | sed 's/<\/p>//'
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
        -h) usage 0 ;;
        -f) echo "Forecast:    $(forecast)";;
        -c) CELSIUS=1 ;;
      esac
    shift
done

# Display Information

echo "Temperature: $(temperature) degrees"
