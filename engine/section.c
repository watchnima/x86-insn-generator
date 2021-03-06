#include "compiler.h"

#include "nasmlib.h"
#include "x86pg.h"
#include "section.h"

void init_text_sec(struct section *data_sec)
{
    data_sec->type = TEXT_SEC;
}

void init_data_sec(struct section *data_sec)
{
    data_sec->type = DATA_SEC;
    /* CONFIG INFO */
    data_sec->datanum = SECTION_DATA_NUM;
    for (int i = 0; i < data_sec->datanum; i++) {
        data_sec->datasizes[i] = 8192;
    }
}
