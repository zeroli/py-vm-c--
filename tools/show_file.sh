set -x
BASEDIR=$(dirname "$0")
TOPDIR="$BASEDIR/.."
python "$BASEDIR/show_file.py" "$TOPDIR/py/$1"
