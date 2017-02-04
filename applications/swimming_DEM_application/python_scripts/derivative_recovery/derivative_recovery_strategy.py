from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7
# importing the Kratos Library
from KratosMultiphysics import *
from KratosMultiphysics.SwimmingDEMApplication import *
# Check that KratosMultiphysics was imported in the main script
CheckForPreviousImport()
import sys

from . import recoverer
from . import standard_recoverer
from . import zhang_guo_recoverer
from . import L2_projection_recoverer
from . import fortin_2012_recoverer

class DerivativeRecoveryStrategy:
    def __init__(self, pp, fluid_model_part, derivative_recovery_tool = None, custom_functions_tool = None):
        self.fluid_model_part = fluid_model_part
        self.derivative_recovery_tool = derivative_recovery_tool
        self.custom_functions_tool = custom_functions_tool
        self.pp = pp
        self.store_full_gradient = self.pp.CFD_DEM.store_full_gradient
        self.mat_deriv_type = pp.CFD_DEM.material_acceleration_calculation_type
        self.laplacian_type = pp.CFD_DEM.laplacian_calculation_type
        self.vorticity_type = pp.CFD_DEM.vorticity_calculation_type
        self.pressure_grad_type = pp.CFD_DEM.pressure_grad_recovery_type
        self.must_reconstruct_gradient = self.laplacian_type in {3, 4, 5, 6} and self.mat_deriv_type in {3, 4}

        if pp.CFD_DEM.fluid_already_calculated: # the fluid has been calculated before, and the derivatives fed to the fluid_model_part
            self.pre_computed_derivatives = pp.CFD_DEM.load_derivatives
        else:
            self.pre_computed_derivatives = False

        self.mat_deriv_tool = self.GetMatDerivTool()
        self.laplacian_tool = self.GetLaplacianTool()
        self.vorticity_tool = self.GetVorticityTool()
        self.velocity_grad_tool = self.GetVelocityGradTool()
        self.pressure_grad_tool = self.GetPressureGradTool()

    def GetMatDerivTool(self):
        if self.pre_computed_derivatives:
            return recoverer.MaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 0:
            return recoverer.EmptyGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 1:
            return standard_recoverer.StandardMaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 2:
            if self.laplacian_type == 2:
                return zhang_guo_recoverer.ZhangGuoMaterialAccelerationAndLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                return zhang_guo_recoverer.ZhangGuoMaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type in {3, 4}:
            return L2_projection_recoverer.L2ProjectionDirectMaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 5:
            return L2_projection_recoverer.L2ProjectionMaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 6:
            return fortin_2012_recoverer.Fortin2012MaterialAccelerationRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.mat_deriv_type == 7:
            if self.store_full_gradient:
                return zhang_guo_recoverer.ZhangGuoMaterialAccelerationAndLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                raise Exception('The value of material_acceleration_calculation_type is ' + str(self.mat_deriv_type) + ' , which is only compatible with store_full_gradient = 1. Instead it is store_full_gradient = ' + str(self.store_full_gradient) + '.')
        else:
            raise Exception('The value of material_acceleration_calculation_type is ' + str(self.mat_deriv_type) + ' , which does not correspond to any valid option.')

    def GetLaplacianTool(self):
        if self.laplacian_type == 0 or self.pre_computed_derivatives:
            return recoverer.EmptyLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.laplacian_type == 1:
            return standard_recoverer.StandardLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.laplacian_type == 2:
            if self.mat_deriv_type == 2:
                return zhang_guo_recoverer.ZhangGuoMaterialAccelerationAndLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                return zhang_guo_recoverer.ZhangGuoDirectLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.laplacian_type in {3, 4, 5, 6}:
            if self.store_full_gradient:
                return L2_projection_recoverer.L2ProjectionLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                raise Exception('The value of laplacian_calculation_type is ' + str(self.laplacian_type) + ' , which is only compatible with store_full_gradient = 1. Instead it is store_full_gradient = ' + str(self.store_full_gradient) + '.')
        elif self.laplacian_type == 7:
            if self.store_full_gradient:
                return zhang_guo_recoverer.ZhangGuoMaterialAccelerationAndLaplacianRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                raise Exception('The value of laplacian_calculation_type is ' + str(self.mat_deriv_type) + ' , which is only compatible with store_full_gradient = 1. Instead it is store_full_gradient = ' + str(self.store_full_gradient) + '.')
        else:
            raise Exception('The value of laplacian_calculation_type is ' + str(self.laplacian_type) + ' , which does not correspond to any valid option.')

    def GetVorticityTool(self):
        if self.pre_computed_derivatives:
            return recoverer.VorticityRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        if self.vorticity_type == 0:
            return recoverer.EmptyVorticityRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.vorticity_type == 5: # NOT WORKING YET WITH VECTORS
            return recoverer.EmptyVorticityRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        else:
            raise Exception('The value of vorticity_calculation_type is ' + str(self.vorticity_type) + ' , which does not correspond to any valid option.')

    def GetVelocityGradTool(self):
        if self.pre_computed_derivatives:
            return recoverer.EmptyGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        if self.must_reconstruct_gradient:
            if self.mat_deriv_tool == 6:
                return fortin_2012_recoverer.Fortin2012GradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
            else:
                return L2_projection_recoverer.L2ProjectionGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        else:
            return recoverer.EmptyGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)

    def GetPressureGradTool(self):
        if self.pressure_grad_type == 0:
            return recoverer.EmptyGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.pressure_grad_type == 1:
            return standard_recoverer.StandardGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        elif self.pressure_grad_type == 2:
            return zhang_guo_recoverer.ZhangGuoGradientRecoverer(self.pp, self.fluid_model_part, self.derivative_recovery_tool)
        else:
            raise Exception('The value of pressure_grad_recovery_type is ' + str(self.pressure_grad_type) + ' , which does not correspond to any valid option.')

    def Recover(self):
        # Some of the following may be empty, and some may do the work of others for efficiency.
        self.mat_deriv_tool.RecoverMaterialAcceleration()
        self.velocity_grad_tool.RecoverGradientOfVelocity()
        self.pressure_grad_tool.RecoverPressureGradient()
        self.laplacian_tool.RecoverVelocityLaplacian()