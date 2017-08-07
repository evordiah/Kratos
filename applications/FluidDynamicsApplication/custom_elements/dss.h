//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//

#ifndef KRATOS_DSS_H
#define KRATOS_DSS_H

#include "includes/define.h"
#include "includes/element.h"
#include "includes/serializer.h"
#include "geometries/geometry.h"

#include "includes/cfd_variables.h"
#include "custom_elements/fluid_element.h"
#include "fluid_dynamics_application_variables.h"

// For body force test
#include <cmath>

namespace Kratos
{

///@addtogroup FluidDynamicsApplication
///@{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

template< class TElementData >
class DSS : public FluidElement<TElementData>
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of DSS
    KRATOS_CLASS_POINTER_DEFINITION(DSS);

    /// Node type (default is: Node<3>)
    typedef Node<3> NodeType;

    /// Geometry type (using with given NodeType)
    typedef Geometry<NodeType> GeometryType;

    /// Definition of nodes container type, redefined from GeometryType
    typedef Geometry<NodeType>::PointsArrayType NodesArrayType;

    /// Vector type for local contributions to the linear system
    typedef Vector VectorType;

    /// Matrix type for local contributions to the linear system
    typedef Matrix MatrixType;

    typedef std::size_t IndexType;

    typedef std::size_t SizeType;

    typedef std::vector<std::size_t> EquationIdVectorType;

    typedef std::vector< Dof<double>::Pointer > DofsVectorType;

    typedef PointerVectorSet<Dof<double>, IndexedObject> DofsArrayType;

    /// Type for shape function values container
    typedef Kratos::Vector ShapeFunctionsType;

    /// Type for a matrix containing the shape function gradients
    typedef Kratos::Matrix ShapeFunctionDerivativesType;

    /// Type for an array of shape function gradient matrices
    typedef GeometryType::ShapeFunctionsGradientsType ShapeFunctionDerivativesArrayType;

    ///@}
    ///@name Life Cycle
    ///@{

    //Constructors.

    /// Default constuctor.
    /**
     * @param NewId Index number of the new element (optional)
     */
    DSS(IndexType NewId = 0);

    /// Constructor using an array of nodes.
    /**
     * @param NewId Index of the new element
     * @param ThisNodes An array containing the nodes of the new element
     */
    DSS(IndexType NewId, const NodesArrayType& ThisNodes);

    /// Constructor using a geometry object.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     */
    DSS(IndexType NewId, GeometryType::Pointer pGeometry);

    /// Constuctor using geometry and properties.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     * @param pProperties Pointer to the element's properties
     */
    DSS(IndexType NewId, GeometryType::Pointer pGeometry, Properties::Pointer pProperties);

    /// Destructor.
    virtual ~DSS();

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{


    /// Create a new element of this type
    /**
     * Returns a pointer to a new DSS element, created using given input
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Element::Pointer Create(IndexType NewId,
                            NodesArrayType const& ThisNodes,
                            Properties::Pointer pProperties) const;


    ///@}
    ///@name Access
    ///@{


    virtual void GetValueOnIntegrationPoints(const Variable<array_1d<double, 3 > >& rVariable,
                                             std::vector<array_1d<double, 3 > >& rValues,
                                             const ProcessInfo& rCurrentProcessInfo);


    virtual void GetValueOnIntegrationPoints(const Variable<double>& rVariable,
                                             std::vector<double>& rValues,
                                             const ProcessInfo& rCurrentProcessInfo);


    virtual void GetValueOnIntegrationPoints(const Variable<array_1d<double, 6 > >& rVariable,
                                             std::vector<array_1d<double, 6 > >& rValues,
                                             const ProcessInfo& rCurrentProcessInfo);


    virtual void GetValueOnIntegrationPoints(const Variable<Vector>& rVariable,
                                             std::vector<Vector>& rValues,
                                             const ProcessInfo& rCurrentProcessInfo);


    virtual void GetValueOnIntegrationPoints(const Variable<Matrix>& rVariable,
                                             std::vector<Matrix>& rValues,
                                             const ProcessInfo& rCurrentProcessInfo);


    ///@}
    ///@name Inquiry
    ///@{

    virtual int Check(const ProcessInfo &rCurrentProcessInfo);

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    virtual std::string Info() const;


    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const;


    ///@}
    ///@name Friends
    ///@{


    ///@}

protected:

    ///@name Protected static Member Variables
    ///@{


    ///@}
    ///@name Protected member Variables
    ///@{


    ///@}
    ///@name Protected Operators
    ///@{


    ///@}
    ///@name Protected Operations
    ///@{


    virtual void ASGSMomentumResidual(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType &rN,
        const ShapeFunctionDerivativesType &rDN_DX,
        array_1d<double,3>& rMomentumRes);


    virtual void ASGSMassResidual(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType &rN,
        const ShapeFunctionDerivativesType &rDN_DX,
        double& rMomentumRes);


    virtual void OSSMomentumResidual(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType &rN,
        const ShapeFunctionDerivativesType &rDN_DX,
        array_1d<double,3>& rMomentumRes);

    virtual void OSSMassResidual(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType& rN,
        const ShapeFunctionDerivativesType& rDN_DX,
        double& rMassRes);


    virtual void MomentumProjTerm(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType &rN,
        const ShapeFunctionDerivativesType &rDN_DX,
        array_1d<double,3>& rMomentumRHS);


    virtual void MassProjTerm(
        const TElementData& rData,
        double GaussIndex,
        const ShapeFunctionsType &rN,
        const ShapeFunctionDerivativesType &rDN_DX,
        double& rMassRHS);


    void ResolvedConvectiveVelocity(array_1d<double,3>& rConvVel,
                                    const ShapeFunctionsType& rN);


    void FullConvectiveVelocity(array_1d<double,3>& rConvVel,
                                const ShapeFunctionsType& rN,
                                const array_1d<double,3>& rSubscaleVel);

    virtual void AddSystemTerms(
        const TElementData& rData,
        unsigned int GaussIndex,
        double GaussWeight,
        const ShapeFunctionsType& rN,
        const ShapeFunctionDerivativesType& rDN_DX,
        const ProcessInfo& rProcessInfo,
        MatrixType& rLHS,
        VectorType& rRHS);


    virtual void AddMassTerms(
        const TElementData& rData,
        double GaussWeight,
        const ShapeFunctionsType& rN,
        MatrixType& rMassMatrix);


    virtual void AddMassStabilization(
        const TElementData& rData,
        unsigned int GaussIndex,
        double GaussWeight,
        const ShapeFunctionsType& rN,
        const ShapeFunctionDerivativesType& rDN_DX,
        const ProcessInfo& rProcessInfo,
        MatrixType& rMassMatrix);

    void CalculateProjections();


    void AddViscousTerm(double DynamicViscosity,
                        double GaussWeight,
                        const ShapeFunctionDerivativesType& rDN_DX,
                        MatrixType& rLHS);


    virtual void SubscaleVelocity(
        const TElementData& rData,
        unsigned int GaussIndex,
        const ShapeFunctionsType& rN,
        const ShapeFunctionDerivativesType& rDN_DX,
        const ProcessInfo& rProcessInfo,
        array_1d<double,3>& rVelocitySubscale);

    virtual void SubscalePressure(
        const TElementData& rData,
        unsigned int GaussIndex,
        const ShapeFunctionsType& rN,
        const ShapeFunctionDerivativesType& rDN_DX,
        const ProcessInfo& rProcessInfo,
        double &rPressureSubscale);

    ///@}
    ///@name Protected  Access
    ///@{


    ///@}
    ///@name Protected Inquiry
    ///@{


    ///@}
    ///@name Protected LifeCycle
    ///@{


    ///@}

private:

    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    ///@}
    ///@name Serialization
    ///@{

    friend class Serializer;

    virtual void save(Serializer& rSerializer) const;

    virtual void load(Serializer& rSerializer);

    ///@}
    ///@name Private Operators
    ///@{


    ///@}
    ///@name Private Operations
    ///@{


    ///@}
    ///@name Private  Access
    ///@{


    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    DSS& operator=(DSS const& rOther);

    /// Copy constructor.
    DSS(DSS const& rOther);

    ///@}


}; // Class DSS

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function
template< class TElementData >
inline std::istream& operator >>(std::istream& rIStream,
                                 DSS<TElementData>& rThis)
{
    return rIStream;
}

/// output stream function
template< class TElementData >
inline std::ostream& operator <<(std::ostream& rOStream,
                                 const DSS<TElementData>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

///@} // Fluid Dynamics Application group

} // namespace Kratos.

#endif // KRATOS_DSS_H