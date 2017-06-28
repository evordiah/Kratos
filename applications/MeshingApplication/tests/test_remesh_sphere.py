# We import the libraies
from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics
import KratosMultiphysics.MeshingApplication as MeshingApplication
import KratosMultiphysics.KratosUnittest as KratosUnittest

class TestRemeshMMG(KratosUnittest.TestCase):
    
    def _test_remesh_sphere(self):
        # We create the model part
        main_model_part = KratosMultiphysics.ModelPart("MainModelPart")
        main_model_part.ProcessInfo.SetValue(KratosMultiphysics.DOMAIN_SIZE, 3)

        # We add the variables needed 
        main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DISTANCE)
        main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DISTANCE_GRADIENT)
        main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NODAL_H)
        main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NODAL_AREA)

        # We import the model main_model_part
        KratosMultiphysics.ModelPartIO("mmg_eulerian_test/coarse_sphere_test").ReadModelPart(main_model_part)

        # We calculate the gradient of the distance variable
        find_nodal_h = KratosMultiphysics.FindNodalHProcess(main_model_part)
        find_nodal_h.Execute()
        local_gradient = KratosMultiphysics.ComputeNodalGradientProcess3D(main_model_part, KratosMultiphysics.DISTANCE, KratosMultiphysics.DISTANCE_GRADIENT, KratosMultiphysics.NODAL_AREA)
        local_gradient.Execute()

        # We set to zero the metric
        ZeroVector = KratosMultiphysics.Vector(6) 
        ZeroVector[0] = 0.0
        ZeroVector[1] = 0.0
        ZeroVector[2] = 0.0
        ZeroVector[3] = 0.0
        ZeroVector[4] = 0.0
        ZeroVector[5] = 0.0

        for node in main_model_part.Nodes:
            node.SetValue(MeshingApplication.MMG_METRIC, ZeroVector)
                
        # We define a metric using the ComputeLevelSetSolMetricProcess
        MetricParameters = KratosMultiphysics.Parameters("""
        {
            "minimal_size"                      : 1.0e-1,
            "anisotropy_remeshing"              : false,
            "anisotropy_parameters"             :{
                "hmin_over_hmax_anisotropic_ratio"  : 0.15,
                "boundary_layer_max_distance"       : 1.0e-4,
                "interpolation"                     : "Linear"
            }
        }
        """)
        metric_process = MeshingApplication.ComputeLevelSetSolMetricProcess3D(main_model_part, KratosMultiphysics.DISTANCE_GRADIENT, MetricParameters)

        metric_process.Execute()

        MMGParameters = KratosMultiphysics.Parameters("""
        {
            "filename"                         : "mmg_eulerian_test/coarse_sphere_test", 
            "save_external_files"              : true,
            "echo_level"                       : 0
        }
        """)

        # We create the remeshing utility
        MmgProcess = MeshingApplication.MmgProcess3D(main_model_part, MMGParameters)

        # We remesh
        MmgProcess.Execute()
        
    def test_execution(self):
        self._test_remesh_sphere()
        
if __name__ == '__main__':
    KratosUnittest.main()