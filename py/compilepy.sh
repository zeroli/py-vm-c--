set -x
BASEDIR=$(dirname "$0")
python -m compileall "$BASEDIR/$1"
