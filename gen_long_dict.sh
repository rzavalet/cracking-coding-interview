#! /bin/sh
#
# gen_long_dict.sh
# Copyright (C) 2022 rzavalet <rzavalet@thinkbook>
#
# Distributed under terms of the MIT license.
#

for i in {1..999}; do cat words_alpha.txt >> long_dict.txt; done
