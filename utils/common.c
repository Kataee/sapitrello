#include "common.h"

#include "../models/card.h"

char *get_status_name(CARD_STATUS status) {
	switch (status) {
		case TODO:
			return "TODO";
		case DOING:
			return "DOING";
		case DONE:
			return "DONE";
	}

	return "<UNKNOWN>";
}
