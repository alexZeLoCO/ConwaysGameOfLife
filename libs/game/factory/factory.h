#ifndef FACTORY_H
#define FACTORY_H

#include <jansson.h>
#include <string.h>

#include "../../board/board.h"
#include "../../error/error.h"

enum Enum_Template {
	BLINKER,
	BEACON,
	TOAD,
	GLIDER,
	LWSS,
	MWSS,
	HWSS,
	GGG,
	SGG,
	PENTOMINO,
	DIEHARD,
	DIAMOND
};

#define template enum Enum_Template

board* get_from_template(template the_template);
board* get_from_file(char* filename);
template get_template_from_name(char* name);
board* get_from_plaintext(char* filename);

#endif
