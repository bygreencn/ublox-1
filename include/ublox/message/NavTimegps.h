//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// @file
/// @brief Contains definition of NAV-TIMEGPS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEGPS message fields.
/// @see NavTimegps
struct NavTimegpsFields
{
    /// @brief Bits access enumeration for bits in @b valid bitmask field
    enum
    {
        valid_towValid, ///< @b towValid bit index
        valid_weekValid, ///< @b weekValid bit index
        valid_leapSValid, ///< @b leapSValid bit index
        valid_numOfValues ///< number of available bits
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "fTOW" field.
    using fTOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using week = field::nav::week;

    /// @brief Definition of "leapS" field.
    using leapS = field::common::I1;

    /// @brief Definition of "valid" field.
    using valid = field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >;

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        fTOW,
        week,
        leapS,
        valid,
        tAcc
    >;
};

/// @brief Definition of NAV-TIMEGPS message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavTimegpsFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimegps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields::All>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields::All>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavTimegpsFields::iTOW
        FieldIdx_fTOW, ///< @b fTOW field, see @ref NavTimegpsFields::fTOW
        FieldIdx_week, ///< @b week field, see @ref NavTimegpsFields::week
        FieldIdx_leapS, ///< @b leapS field, see @ref NavTimegpsFields::leapS
        FieldIdx_valid, ///< @b valid field, see @ref NavTimegpsFields::valid
        FieldIdx_tAcc, ///< @b tAcc field, see @ref NavTimegpsFields::tAcc
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavTimegps() = default;

    /// @brief Copy constructor
    NavTimegps(const NavTimegps&) = default;

    /// @brief Move constructor
    NavTimegps(NavTimegps&& other) = default;

    /// @brief Destructor
    virtual ~NavTimegps() = default;

    /// @brief Copy assignment
    NavTimegps& operator=(const NavTimegps&) = default;

    /// @brief Move assignment
    NavTimegps& operator=(NavTimegps&&) = default;
};


}  // namespace message

}  // namespace ublox





