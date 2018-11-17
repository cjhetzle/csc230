/**
  @file edit.c
  @author Cameron Hetzler cjhetzle
*/

#include "edit.h"

Edit *makeInsert( Document *doc, int ch ) {

  return NULL;
}

Edit *makeDelete( Document *doc ) {

  return NULL;
}

void initHistory( History *hist ) {

}

void clearHistory( History *hist ) {

}

void applyEdit( History *hist, Document *doc, Edit *edit ) {

}

bool undoEdit( History *hist, Document *doc ) {

  return false;
}

bool redoEdit( History *hist, Document *doc ) {

  return false;
}