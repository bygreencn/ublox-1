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
/// @brief Contains definition of LOG-CREATE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-CREATE message fields.
/// @see LogCreate
struct LogCreateFields
{
    /// @brief Value enumeration for @ref logSize field
    enum class LogSize : std::uint8_t
    {
        Max, ///< maximum
        Min, ///< minimum
        UserDefined, ///< user defined
        NumOfValues ///< number of values
    };

    /// @brief Bits access enumeration for @ref logCfg bitmask field.
    enum
    {
        logCfg_circular, ///< @b circular bit index
        logCfg_numOfValues ///< number of available bits
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "logCfg" field.
    using logCfg =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >;

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res1;

    /// @brief Definition of "logSize" field.
    using logSize  =
        field::common::EnumT<
            LogSize,
            comms::option::ValidNumValueRange<0, (int)LogSize::NumOfValues - 1>
        >;

    /// @brief Definition of "userDefinedSize" field.
    using userDefinedSize = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        logCfg,
        reserved,
        logSize,
        userDefinedSize
    >;
};

/// @brief Definition of LOG-CREATE message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref LogCreateFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogCreate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields::All>,
        comms::option::DispatchImpl<LogCreate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields::All>,
        comms::option::DispatchImpl<LogCreate<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref LogCreateFields::version
        FieldIdx_logCfg, ///< @b logCfg field, see @ref LogCreateFields::logCfg
        FieldIdx_reserved, ///< @b reserved field, see @ref LogCreateFields::reserved
        FieldIdx_logSize, ///< @b logSize field, see @ref LogCreateFields::logSize
        FieldIdx_userDefinedSize, ///< @b userDefinedSize field, see @ref LogCreateFields::userDefinedSize
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogCreate() = default;

    /// @brief Copy constructor
    LogCreate(const LogCreate&) = default;

    /// @brief Move constructor
    LogCreate(LogCreate&& other) = default;

    /// @brief Destructor
    virtual ~LogCreate() = default;

    /// @brief Copy assignment
    LogCreate& operator=(const LogCreate&) = default;

    /// @brief Move assignment
    LogCreate& operator=(LogCreate&&) = default;
};


}  // namespace message

}  // namespace ublox

