///\cond
#include <iostream>
#include <math.h>
///\endcond
#include "Topology1d.h"
#include "TopologyTriangle.h"
#include "TopologyQuad.h"
#include "TopologyTetrahedron.h"
#include "Analysis.h"
#include "VTKGeoMesh.h"
#include "ReadGmsh.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "L2Projection.h"
#include "CompElement.h"

using std::cout;
using std::endl;
using std::cin;


int main() {
    /*
    VecDouble phir(2), phitheta(2);
    MatrixDouble dphir(1, 2), dphitheta(1, 2);
    VecDouble xp;
    int order = 1;
    MatrixDouble jac(2, 2);

    double Integral = 0;
    IntRuleQuad rule(1);
    int np = rule.NPoints();
    for (int ip = 0; ip < np; ip++)
    {
        VecDouble xip(2);
        double wp;
        rule.Point(ip, xip, wp);

        double r = (xip[0] - 1.) / 2. + 5. * (xip[0] + 1.) / 2.;
        double drdxi = 1. / 2. + 5. / 2.;
        double theta = M_PI / 2. * (xip[1] + 1.) / 2.;
        double dthetadeta = M_PI / 4.;
        // x = r cos(theta)
        // y = r sin(theta)
        // dxdr = r' cos(theta)
        jac(0, 0) = drdxi * cos(theta);
        // dxdtheta = -r sin(theta) theta'
        jac(0, 1) = -r * sin(theta) * dthetadeta;
        // dydr = r' sin(theta)
        jac(1, 0) = drdxi * sin(theta);
        // dydtheta = r cos(theta) theta'
        jac(1, 1) = r * cos(theta) * dthetadeta;
        double detjac = std::abs(jac.determinant());
        Integral += detjac * wp;
    }

    std::cout << "order = " << order << " integral aproximada " << Integral <<
        " erro " << 6. * M_PI - Integral << std::endl;
    */


    GeoMesh gmesh;
    ReadGmsh read;
    read.Read(gmesh, "quads.msh");
    VTKGeoMesh plotmesh;
    plotmesh.PrintGMeshVTK(&gmesh, "quads.vtk");



    CompMesh cmesh(&gmesh);
    MatrixDouble perm(3, 3);
    perm.setZero();
    perm(0, 0) = 1.;
    perm(1, 1) = 1.;
    perm(2, 2) = 1.;
    Poisson* mat1 = new Poisson(3, perm);

    MatrixDouble proj(1, 1), val1(1, 1), val2(1, 1);
    proj.setZero();
    val1.setZero();
    val2.setZero();
    L2Projection* bc_linha = new L2Projection(0, 2, proj, val1, val2);
    L2Projection* bc_point = new L2Projection(0, 1, proj, val1, val2);
    std::vector<MathStatement*> mathvec = { 0,bc_point,bc_linha,mat1 };

    cmesh.SetMathVec(mathvec);
    cmesh.AutoBuild();
    cmesh.Resequence();
    cmesh.Solution() (0, 0) = 1.0;
    plotmesh.PrintCMeshVTK(&cmesh, 2, "quads_malha.vtk");


    int nsol = cmesh.Solution().rows();
    for (int isol = 0; isol < nsol; isol++)
    {
        std::stringstream sout;
        sout << "cmesh_quads." << isol << ".vtk";
        cmesh.Solution().setZero();
        cmesh.Solution()[isol] = 1.;
        plotmesh.PrintCMeshVTK(&cmesh, 2, sout.str());
    }

    return 0;

}