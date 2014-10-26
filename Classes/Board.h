#pragma once

#include <vector>
#include <map>
#include <set>

class BoardListener;

class Board
{

public:
    using CellValue = unsigned;
    using Row = ::std::vector<CellValue>;
    using Rows = ::std::vector<Row>;
    using Index = ::std::pair<int, int>;
    using Indeces = ::std::vector<Index>;

    enum class MovementType {
        kUp,
        kDown,
        kLeft,
        kRight
    };

    explicit Board(unsigned size);

    unsigned size() const { return size_; }
    const Rows &rows() const { return rows_; }

    void addListener(BoardListener* listener){ listeners_.insert(listener); }

    void spawnNew();
    void move(MovementType type);

private:
    Row merge(const Row &row, const Indeces &row_indeces);

    using NotifyFunctor = ::std::function<void(BoardListener *listener)>;
    void notifyListeners(const NotifyFunctor &functor);

private:
    unsigned size_;
    Rows rows_;

    const ::std::map<MovementType, Index> kOffsets =
            {
                    { MovementType::kUp, {1, 0} },
                    { MovementType::kDown, {-1, 0} },
                    { MovementType::kLeft, {0, 1} },
                    { MovementType::kRight, {0, -1} }
            };

    ::std::map<MovementType, Indeces> start_indeces_;

    using Listeners = ::std::set<BoardListener *>;
    Listeners listeners_;
};

class BoardListener
{
protected:
    using Index = Board::Index;
    using Rows = Board::Rows;
    using CellValue = Board::CellValue;

public:
    virtual void onCellMoved(const Index &startIndex, const Index &endIndex) = 0;
    virtual void onCellUpdated(const Index &index, CellValue value) = 0;
    virtual void onUpdated(const Rows &rows) = 0;
};