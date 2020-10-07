#include "customtool.h"

CustomTool::CustomTool() {

}

qreal CustomTool::mapInt2Real(int i_min, int i_max, qreal r_min, qreal r_max, int value) {
    return r_min + (r_max - r_min) * (1.0 * (value - i_min) / (i_max - i_min));
}
