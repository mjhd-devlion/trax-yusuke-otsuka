#include "ArrayBoard.h"

#include <cstring>

ArrayBoard::ArrayBoard() {
    this->_left   = 256;
    this->_top    = 256;
    this->_right  = 256;
    this->_bottom = 256;

    std::memset(this->_board, 0, sizeof(Cell) * 512 * 512);
}

Cell& ArrayBoard::operator()(Coord x, Coord y) {

#ifndef _NO_VALIDATIONS_
    if ((x >= this->Width()) ||
        (y >= this->Height()))
        throw "Out of Range";
#endif

    if (this->_right  == this->_leftInChange + x) this->_rightInChange  = this->_right  + 1;
    if (this->_bottom == this->_topInChange  + y) this->_bottomInChange = this->_bottom + 1;
    if (this->_leftInChange + x == this->_left) this->_leftInChange = this->_left - 1;
    if (this->_topInChange  + y == this->_top)  this->_topInChange  = this->_top  - 1;

    return this->_board[this->_left + x][this->_top + y];
}

const Cell& ArrayBoard::Get(Coord x, Coord y) const {
#ifndef _NO_VALIDATIONS_
    if ((x >= this->Width()) ||
        (y >= this->Height()))
        return EmptyCell;
#endif

    return this->_board[this->_left + x][this->_top + y];
}

Coord ArrayBoard::Width() const {
    return this->_right - this->_left + 1;
}

Coord ArrayBoard::Height() const {
    return this->_bottom - this->_top + 1;
}

void ArrayBoard::BeginChange() {
    this->_leftInChange   = this->_left;
    this->_topInChange    = this->_top;
    this->_rightInChange  = this->_right;
    this->_bottomInChange = this->_bottom;
}

void ArrayBoard::EndChange() {
    this->_left   = this->_leftInChange;
    this->_top    = this->_topInChange;
    this->_right  = this->_rightInChange;
    this->_bottom = this->_bottomInChange;
}
