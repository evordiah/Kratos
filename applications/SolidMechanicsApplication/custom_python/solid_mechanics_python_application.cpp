//
//   Project Name:        KratosSolidMechanicsApplication $
//   Created by:          $Author:            JMCarbonell $
//   Last modified by:    $Co-Author:                     $
//   Date:                $Date:                July 2013 $
//   Revision:            $Revision:                  0.0 $
//
//

// System includes
#if defined(KRATOS_PYTHON)

// External includes
#include <boost/python.hpp>

// Project includes
#include "custom_python/add_custom_strategies_to_python.h"
#include "custom_python/add_custom_utilities_to_python.h"
#include "custom_python/add_custom_constitutive_laws_to_python.h"
#include "custom_python/add_custom_processes_to_python.h"

#include "solid_mechanics_application.h"

namespace Kratos
{

namespace Python
{

using namespace boost::python;



BOOST_PYTHON_MODULE(KratosSolidMechanicsApplication)
{

    class_<KratosSolidMechanicsApplication,
           KratosSolidMechanicsApplication::Pointer,
           bases<KratosApplication>, boost::noncopyable >("KratosSolidMechanicsApplication")
           ;

    AddCustomUtilitiesToPython();
    AddCustomStrategiesToPython();
    AddCustomConstitutiveLawsToPython(); 
    AddCustomProcessesToPython();
    
    //registering variables in python ( if must to be seen from python )

    //For process information
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( LOAD_RESTART )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( COMPUTE_LUMPED_MASS_MATRIX )
   
    //For explicit schemes
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( MIDDLE_VELOCITY )
            
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( POINT_LOAD )
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( LINE_LOAD )
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( SURFACE_LOAD )

    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( POINT_MOMENT )

    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( FOLLOWER_POINT_LOAD )
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( FOLLOWER_LINE_LOAD )
    KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS( FOLLOWER_SURFACE_LOAD )
      
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( LINE_LOADS_VECTOR )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( SURFACE_LOADS_VECTOR )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( CONSTITUTIVE_LAW_NAME )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( WRITE_ID )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( PREVIOUS_DELTA_TIME )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( RAYLEIGH_ALPHA )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( RAYLEIGH_BETA )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( EXTERNAL_FORCES_VECTOR )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( INTERNAL_FORCES_VECTOR )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( CONTACT_FORCES_VECTOR )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( STABILIZATION_FACTOR )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( PRESSURE_REACTION )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( CAUCHY_STRESS_VECTOR )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( DEFORMATION_GRADIENT )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( ALMANSI_STRAIN_TENSOR )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( PK2_STRESS_TENSOR )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( VON_MISES_STRESS )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( PLASTIC_STRAIN )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( DELTA_PLASTIC_STRAIN )

    KRATOS_REGISTER_IN_PYTHON_VARIABLE( DETERMINANT_F )
       
    // material orientation
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( MATERIAL_ORIENTATION_DX )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( MATERIAL_ORIENTATION_DY )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( MATERIAL_ORIENTATION_DZ )
    
    // orthotropic/anisotropic constants
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( YOUNG_MODULUS_X )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( YOUNG_MODULUS_Y )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( YOUNG_MODULUS_Z )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( SHEAR_MODULUS_XY )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( SHEAR_MODULUS_YZ )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( SHEAR_MODULUS_XZ )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( POISSON_RATIO_XY )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( POISSON_RATIO_YZ )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( POISSON_RATIO_XZ )
    
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( REFERENCE_TEMPERATURE )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( PLASTIC_DISSIPATION )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( DELTA_PLASTIC_DISSIPATION )

    //material : hardening
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( ISOTROPIC_HARDENING_MODULUS )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( KINEMATIC_HARDENING_MODULUS )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( HARDENING_EXPONENT )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( REFERENCE_HARDENING_MODULUS )
    KRATOS_REGISTER_IN_PYTHON_VARIABLE( INFINITY_HARDENING_MODULUS )
      
    //material : isotropic damage
    KRATOS_REGISTER_IN_PYTHON_VARIABLE(DAMAGE_VARIABLE)

}


}  // namespace Python.

}  // namespace Kratos.

#endif // KRATOS_PYTHON defined
