# hijridate

Display the current date/time in the given FORMAT, with support for Hijri (Islamic) date.


## Installation

```sh
cd hijridate
make
./hijridate -h
```

## Usage

```sh
Usage: hijridate [OPTION] [+FORMAT]
Display the current date/time in the given FORMAT.

OPTION:

  -h, --help     display this help and exit
      --version  output version information and exit

FORMAT: controls the output.  Interpreted sequences are:
        must start with +

Hijri (Islamic):
  %HY   hijri year
  %HM   hijri month (01..12)
  %HD   hijri day of month (e.g., 01)
  %HA   locale's full weekday name (e.g., Ahad)
  %HB   locale's full month name (e.g., Ramadan)
  %Ha   locale's abbreviated weekday name (e.g., Ahd)
  %Hb   locale's abbreviated month name (e.g., Ram)
Gregorian (Christian):
  %GY   greforian year
  %GM   greforian month (01..12)
  %GD   greforian day of month (e.g., 01)
  %GA   locale's full weekday name (e.g., Sunday)
  %GB   locale's full month name (e.g., January)
  %Ga   locale's abbreviated weekday name (e.g., Sun)
  %Gb   locale's abbreviated month name (e.g., Jan)
Time:
  %h    hour (00..23)
  %m    minute (00..59)
  %s    second (00..60)


Examples:
  $ hijridate '+%HY %HM %HD %h:%m:%s'
```
