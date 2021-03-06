/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "ThermoPhaseModel.H"

#include "phaseSystem.H"

#include "fvmDdt.H"
#include "fvmDiv.H"
#include "fvmSup.H"
#include "fvmLaplacian.H"
#include "fvcDdt.H"
#include "fvcDiv.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ThermoType>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::ThermoPhaseModel
(
    const phaseSystem& fluid,
    const word& phaseName,
    const label index
)
:
    BasePhaseModel(fluid, phaseName, index),
    thermo_(ThermoType::New(fluid.mesh(), this->name()))
{
    thermo_->validate
    (
        IOobject::groupName(phaseModel::typeName, this->name()),
        "h",
        "e"
    );
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ThermoType>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::~ThermoPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel, class ThermoType>
bool Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::incompressible() const
{
    return thermo_().incompressible();
}


template<class BasePhaseModel, class ThermoType>
bool Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::isochoric() const
{
    return thermo_().isochoric();
}


template<class BasePhaseModel, class ThermoType>
const Foam::rhoThermo&
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::thermo() const
{
    return thermo_();
}


template<class BasePhaseModel, class ThermoType>
Foam::rhoThermo&
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::thermoRef()
{
    return thermo_();
}


template<class BasePhaseModel, class ThermoType>
Foam::tmp<Foam::volScalarField>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::rho() const
{
    return thermo_->rho();
}


template<class BasePhaseModel, class ThermoType>
Foam::tmp<Foam::volScalarField>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::mu() const
{
    return thermo_->mu();
}


template<class BasePhaseModel, class ThermoType>
Foam::tmp<Foam::scalarField>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::mu
(
    const label patchi
) const
{
    return thermo_->mu(patchi);
}


template<class BasePhaseModel, class ThermoType>
Foam::tmp<Foam::volScalarField>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::nu() const
{
    return thermo_->nu();
}


template<class BasePhaseModel, class ThermoType>
Foam::tmp<Foam::scalarField>
Foam::ThermoPhaseModel<BasePhaseModel, ThermoType>::nu
(
    const label patchi
) const
{
    return thermo_->nu(patchi);
}


// ************************************************************************* //
