#! /bin/sh

# This is a little Shell Script that allows you to upload files to the
# SuperTux MediaWiki. To use it to create a file ~/.tuxjunior-wiki.sh
# and fill it with:
#
# WIKI_USERNAME=""
# WIKI_PASSWORD=""
#
# Then just upload files with:
#
#   upload_tuxjunior_wiki.sh your_file.png "Your Description"
#

set -e

function rc_error() {
    echo "Create a file ~/.tuxjunior-wiki.sh with the following syntax: "
    echo ""
    echo "WIKI_USERNAME=your_username"
    echo "WIKI_PASSWORD=your_password"
    echo ""
    exit 1;
}

if [ ! -f ~/.tuxjunior-wiki.sh ]; then
    echo "Error: Couldn't find ~/.tuxjunior-wiki.sh"
    echo ""
    rc_error
fi

source ~/.tuxjunior-wiki.sh

if [ -z "$WIKI_PASSWORD" -o -z "$WIKI_USERNAME" ]; then
    echo "Error: WIKI_PASSWORD or WIKI_USERNAME not set"
    echo ""
    rc_error
fi

usage="\
Usage: $0 [OPTIONS] FILENAME DESCRIPTION

  --overwrite    Overwrite a file in the wiki with the same filename
"

if [ ! $# -eq 2 ]; then
    if [ $# -eq 3 -a "x$1" = "x--overwrite" ]; then
        FILENAME="$2"
        DESCRIPTION="$3"
        IGNORE_WARNING="-F wpIgnoreWarning=1"
    else
      echo "${usage}" 1>&2
      exit 1
    fi
else
    FILENAME="$1"
    DESCRIPTION="$2"
    IGNORE_WARNING=""
fi

if [ ! -r "$FILENAME" ]; then
    echo "Error: Can't read $FILENAME"
    exit 1
fi

# MD5SUM=`md5sum "$1" | cut -c "1-32"`
# echo "MD5Sum: $MD5SUM"

STEP1_FILE="`tempfile`"
STEP2_FILE="`tempfile`"
COOKIES_FILE="`tempfile`"

curl \
 -c "$COOKIES_FILE" \
 -F "wpName=$WIKI_USERNAME"        \
 -F "wpPassword=$WIKI_PASSWORD"    \
 -F "wpLoginattempt=Log in" \
 "http://tuxjunior.berlios.de/wiki/index.php?title=Special:Userlogin&amp;action=submitlogin&amp;returnto=Main_Page" > $STEP1_FILE

curl \
 -b "${COOKIES_FILE}" \
 -F "wpUploadFile=@${FILENAME}" \
 -F "wpUploadDescription=${DESCRIPTION}"  \
 -F "wpUploadAffirm=1" \
 -F "wpUpload='Upload file'" \
 $IGNORE_WARNING \
 "http://tuxjunior.berlios.de/wiki/index.php/Special:Upload" > $STEP2_FILE

echo "------------------------------------------------------------------------"

links -dump $STEP2_FILE  | sed "s/ *Views/## EOF ##/;/## EOF ##/q"

rm -f "$STEP1_FILE" "$STEP2_FILE" "$COOKIES_FILE"

WIKI_FILENAME=$(basename $FILENAME | sed -n "s/^\(.\).*/\1/p" | tr '[a-z]' '[A-Z]')$(basename $FILENAME | sed "s/^.\(.*\)/\1/")

echo ""
echo "Link to the Image list:"
echo "  http://tuxjunior.berlios.de/wiki/index.php/Special:Imagelist"
echo " "
echo "Link to the Image page:" 
echo "  http://tuxjunior.berlios.de/wiki/index.php/Image:"$WIKI_FILENAME
echo ""
echo "Wiki Link (first without thumbnail, second with):"
echo "  [[:Image:$WIKI_FILENAME|$DESCRIPTION]]"
echo "  [[Image:$WIKI_FILENAME|$DESCRIPTION]]"
echo ""

# EOF #
