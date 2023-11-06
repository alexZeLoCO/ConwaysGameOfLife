#ifndef FACTORY_H
#define FACTORY_H

#include <jansson.h>
#include <string.h>

#include "../../board/board.h"
#include "../../logging/error/error.h"
#include "../../logging/log/log.h"

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

template get_template_from_name(char*);
board* get_from_template(template, int);
board* get_from_json(char*, int);
board* get_from_rle(char*, int);
board* get_from_plaintext(char*, int);

#endif
