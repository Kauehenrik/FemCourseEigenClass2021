/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 ///\cond
#include <iostream> 
///\endcond
#include "IntRuleTriangle.h"

IntRuleTriangle::IntRuleTriangle() {

}

IntRuleTriangle::IntRuleTriangle(int order) {
    SetOrder(order);
}

long double ca_4a = 0.44594849091596488631832925388305199;
long double ca_4b = 0.09157621350977074345957146340220151;
long double ca_5a = 0.10128650732345633880098736191512383;
long double ca_5b = 0.47014206410511508977044120951344760;

void IntRuleTriangle::SetOrder(int order) {
    fOrder = order;
    if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }
    switch (order)
    {
    case 0:
    case 1:
        fPoints.resize(1, 2);
        fWeights.resize(1);
        fPoints(0, 0) = 1. / 3.;
        fPoints(0, 1) = 1. / 3.;
        fWeights[0] = 1. / 2.;
        break;

    case 2:
        fPoints.resize(3, 2);
        fWeights.resize(3);
        fPoints(0, 0) = 1. / 2.;
        fPoints(0, 1) = 1. / 2.;
        fPoints(1, 0) = 0.;
        fPoints(1, 1) = 1. / 2.;
        fPoints(2, 0) = 1. / 2.;
        fPoints(2, 1) = 0.;
        fWeights[0] = 1. / 6.;
        fWeights[1] = 1. / 6.;
        fWeights[2] = 1. / 6.;
        break;
    case 3:
        fPoints.resize(4, 2);
        fWeights.resize(4);
        fPoints(0, 0) = 1. / 3.;
        fPoints(0, 1) = 1. / 3.;
        fPoints(1, 0) = 1. / 5.;
        fPoints(1, 1) = 1. / 5.;
        fPoints(2, 0) = 3. / 5.;
        fPoints(2, 1) = 1. / 5.;
        fPoints(3, 0) = 1. / 5.;
        fPoints(3, 1) = 3. / 5.;
        fWeights[0] = -27. / 96.;
        fWeights[1] = 25. / 96.;
        fWeights[2] = 25. / 96.;
        fWeights[3] = 25. / 96.;
        break;

    case 4:
        fPoints.resize(6, 2);
        fWeights.resize(6);

        fPoints(0, 0) = ca_4a;
        fPoints(0, 1) = ca_4a;
        fPoints(1, 0) = 1. - 2. * ca_4a;
        fPoints(1, 1) = ca_4a;
        fPoints(2, 0) = ca_4a;
        fPoints(2, 1) = 1. - 2. * ca_4a;

        fPoints(3, 0) = ca_4b;
        fPoints(3, 1) = ca_4b;
        fPoints(4, 0) = 1. - 2. * ca_4b;
        fPoints(4, 1) = ca_4b;
        fPoints(5, 0) = ca_4b;
        fPoints(5, 1) = 1. - 2. * ca_4b;

        fWeights[0] = 0.22338158967801146569500700843312280 / 2.;
        fWeights[1] = 0.22338158967801146569500700843312280 / 2.;
        fWeights[2] = 0.22338158967801146569500700843312280 / 2.;
        fWeights[3] = 0.10995174365532186763832632490021053 / 2.;
        fWeights[4] = 0.10995174365532186763832632490021053 / 2.;
        fWeights[5] = 0.10995174365532186763832632490021053 / 2.;
        break;

    case 5:

        fPoints.resize(7, 2);
        fWeights.resize(7);

        fPoints(0, 0) = ca_5a;
        fPoints(0, 1) = ca_5a;
        fPoints(1, 0) = 1. - 2. * ca_5a;
        fPoints(1, 1) = ca_5a;
        fPoints(2, 0) = ca_5a;
        fPoints(2, 1) = 1. - 2. * ca_5a;

        fPoints(3, 0) = ca_5b;
        fPoints(3, 1) = ca_5b;
        fPoints(4, 0) = 1. - 2. * ca_5b;
        fPoints(4, 1) = ca_5b;
        fPoints(5, 0) = ca_5b;
        fPoints(5, 1) = 1. - 2. * ca_5b;

        fPoints(6, 0) = 1. / 3.;
        fPoints(6, 1) = 1. / 3.;

        fWeights[0] = ((155. - sqrt(15.)) / 1200.) / 2.;
        fWeights[1] = ((155. - sqrt(15.)) / 1200.) / 2.;
        fWeights[2] = ((155. - sqrt(15.)) / 1200.) / 2.;
        fWeights[3] = ((155. + sqrt(15.)) / 1200.) / 2.;
        fWeights[4] = ((155. + sqrt(15.)) / 1200.) / 2.;
        fWeights[5] = ((155. + sqrt(15.)) / 1200.) / 2.;
        fWeights[6] = (9. / 40.) / 2.;
        break;

    default:
        DebugStop();
        break;
    }
}