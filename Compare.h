
#ifndef MTM_EX2_B_GAME_COMPARE_H
#define MTM_EX2_B_GAME_COMPARE_H


namespace mtm{
    class compare {
    public:
        /** function object
         * compare between 2 GridPoints
         * @param first - the first GridPoint to compare
         * @param second - the second GridPoint to compare
         * @return true if the second is bigger, else otherwise.
         **/
        bool operator()(const GridPoint& first,const GridPoint& second) {
            if(second.row > first.row) {
                return true;
            }
            if(first.row == second.row && second.col > first.col){
                return true;
            }
            return false; }
    };
}

#endif //MTM_EX2_B_GAME_COMPARE_H
