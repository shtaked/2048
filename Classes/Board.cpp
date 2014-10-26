#include "Board.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

Board::Board(unsigned size)
        : size_(size),
          rows_(Rows(size, Row(size, 0)))
{
    std::srand(std::time(0));
    for (int i=0; i<size; ++i) {
        start_indeces_[MovementType::kUp].emplace_back(0, i);
        start_indeces_[MovementType::kDown].emplace_back(size - 1, i);
        start_indeces_[MovementType::kLeft].emplace_back(i, 0);
        start_indeces_[MovementType::kRight].emplace_back(i, size - 1);
    }
};

void Board::spawnNew()
{
    while (true) {
        unsigned x = ::std::rand() % size_;
        unsigned y = ::std::rand() % size_;
        if (rows_[x][y] == 0) {
            rows_[x][y] = 2;

            notifyListeners([index = ::std::make_pair(x, y)](BoardListener *listener) {
                listener->onCellUpdated(index, 2);
            });

            break;
        }
    }
}

void Board::move(MovementType type)
{
    auto start_indeces = start_indeces_[type];
    auto offset = kOffsets.at(type);
    bool was_changed = false;
    for (const auto &start_index : start_indeces)
    {
        //find row to change
        Row row_to_merge;
        Indeces indeces_to_merge;
        auto it_index = start_index;
        while (it_index.first >= 0 && it_index.first < size_
                && it_index.second >= 0 && it_index.second < size_)
        {
            row_to_merge.push_back(rows_[it_index.first][it_index.second]);
            indeces_to_merge.emplace_back(it_index);
            it_index.first += offset.first;
            it_index.second += offset.second;
        }

        //merge this row
        auto result_row = merge(row_to_merge, indeces_to_merge);

        //assign new row
        it_index = start_index;
        int counter = 0;
        while (it_index.first >= 0 && it_index.first < size_
                && it_index.second >= 0 && it_index.second < size_)
        {
            if (rows_[it_index.first][it_index.second] != result_row[counter]) {
                rows_[it_index.first][it_index.second] = result_row[counter];
                was_changed = true;
            }

            it_index.first += offset.first;
            it_index.second += offset.second;

            ++counter;
        }
    }

    if (was_changed) {

        notifyListeners([this](BoardListener *listener) {
            listener->onUpdated(this->rows_);
        });

        spawnNew();
    }
}

Board::Row Board::merge(const Row &row, const Indeces &row_indeces)
{
    Row result_row(row.size(), 0);

    CellValue last_added_value = 0;
    int last_added_pos = -1;
    auto cur_pos = 0;
    for (const auto &cell_value : row) {
        if (cell_value != 0) {
            if (last_added_value != cell_value) {
                result_row[++last_added_pos] = cell_value;
                last_added_value = cell_value;

                if (cur_pos != last_added_pos) {
                    notifyListeners([index_begin = row_indeces.cbegin() + cur_pos,
                                     index_end = row_indeces.cbegin() + last_added_pos]
                                    (BoardListener *listener) {
                        listener->onCellMoved(*index_begin, *index_end);
                    });
                }
            } else {
                result_row[last_added_pos] += cell_value;
                last_added_value = 0;

                if (cur_pos != last_added_pos) {
                    notifyListeners([index_begin = row_indeces.cbegin() + cur_pos,
                            index_end = row_indeces.cbegin() + last_added_pos]
                            (BoardListener *listener) {
                        listener->onCellMoved(*index_begin, *index_end);
                    });
                }
            }
        }

        ++cur_pos;
    }

    return result_row;
}

void Board::notifyListeners(const NotifyFunctor &functor)
{
    auto listeners_it = listeners_.begin();
    while (listeners_it != listeners_.end())
    {
        functor(*listeners_it);
//        if (auto spt = listeners_it->lock()) {
//            functor(spt.get());
            ++listeners_it;
//        } else {
//            listeners_it = listeners_.erase(listeners_it);
//        }
    }
}
