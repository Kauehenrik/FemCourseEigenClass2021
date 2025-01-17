//
//  TestOneDProblem.cpp
//  FemSC
//
//  Created by Eduardo Ferri on 08/17/15.
//
//
//TestOneDProblem cpp
/*
        Os testes foram preparados com um proposito educacional,
        recomenda-se que o aluno entenda a funcionalidade de cada
        teste e posteriormente use com seu código caso a caso
*/
//      Obs: O xmax e xmin estao tomados como 4 e 0, respectivamente,
//      caso estes valores sejam alterados, editar o teste TestNodes.
//
//
#include <iostream>
#include <math.h>
#include "GeoMesh.h"
#include "ReadGmsh.h"
#include "CompMesh.h"
#include "GeoElement.h"
#include "GeoElementTemplate.h"
#include "MathStatement.h"
#include "L2Projection.h"
#include "Analysis.h"
#include "IntRule.h"
#include "PostProcessTemplate.h"
#include "Poisson.h"
#include "VTKGeoMesh.h"

using std::cout;
using std::endl;
using std::cin;

void exact(const VecDouble& point, VecDouble& val, MatrixDouble& deriv);

int main()
{
    GeoMesh gmesh;
    ReadGmsh read;

    /*
    Malha 1D
    std::string filename("1.msh");
    std::string filename("2.msh");
    std::string filename("3.msh");
    std::string filename("4.msh");
    std::string filename("5.msh");
    std::string filename("6.msh");
    */
    std::string filename("6.msh");

    read.Read(gmesh, filename);

    CompMesh cmesh(&gmesh);
    MatrixDouble perm(3, 3);
    perm.setZero();
    perm(0, 0) = 1.;
    perm(1, 1) = 1.;
    perm(2, 2) = 1.;
    Poisson* mat1 = new Poisson(1, perm);
    mat1->SetExactSolution(exact);
    mat1->SetDimension(1);


    auto force = [](const VecDouble& x, VecDouble& res)
    {
        res[0] = -6.*(-2.+ x[0]);
    
    };

    mat1->SetForceFunction(force);
    MatrixDouble proj(1, 1), val1(1, 1), val2(1, 1);
    proj.setZero();
    val1.setZero();
    val2.setZero();
    L2Projection* bc_linha = new L2Projection(0, 2, proj, val1, val2);
    L2Projection* bc_point = new L2Projection(0, 3, proj, val1, val2);
    std::vector<MathStatement*> mathvec = { 0,mat1,bc_linha,bc_point };


    cmesh.SetMathVec(mathvec);
    cmesh.SetDefaultOrder(1);
    cmesh.AutoBuild();
    cmesh.Resequence();


    Analysis AnalysisLoc(&cmesh);
    AnalysisLoc.RunSimulation();


    PostProcessTemplate<Poisson> postprocess;
    postprocess.SetExact(exact);


    VecDouble errvec;
    errvec = AnalysisLoc.PostProcessError(std::cout, postprocess);

    /*
   Malha 1D
   std::string filenamevtk("1.vtk");
   std::string filenamevtk("2.vtk");
   std::string filenamevtk("3.vtk");
   std::string filenamevtk("4.vtk");
   std::string filenamevtk("5.vtk");
   std::string filenamevtk("6.vtk");
   */
    std::string filenamevtk("6.vtk");

    VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, filenamevtk);

    return 0;
}


void exact(const VecDouble& point, VecDouble& val, MatrixDouble& deriv) {


    deriv(0, 0) = (-4. + point[0]) * (-2. + point[0]) + (-4. + point[0]) * point[0] + (-2. + point[0]) * point[0];

    val[0] = point[0] * (2. - point[0])* (4. - point[0]);
    
    return;

}

