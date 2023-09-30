################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify            #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       August 31, 2021                                                #
################################################################################
OUT=done.txt
BUILD_DIR=build

TWO_SRCS=$(shell find 2d/ -name "*.asy")
THREE_SRCS=$(shell find 3d/ -name "*.asy")

TWO_OBJS=$(TWO_SRCS:%.asy=$(BUILD_DIR)/%.pdf)
THREE_OBJS=$(THREE_SRCS:%.asy=$(BUILD_DIR)/%.pdf)

.PHONY: clean all

all: $(OUT)

$(OUT): $(TWO_OBJS) $(THREE_OBJS)
	touch done.txt

$(BUILD_DIR)/%.pdf: %.asy
	@mkdir -p $(@D)
	asy -f "pdf" $< -o $@
	@ln -sf $@ ../images/

clean:
	rm -rf $(BUILD_DIR)
	find ../images/ -type l -exec unlink {} \;
