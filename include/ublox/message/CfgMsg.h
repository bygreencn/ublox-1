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
/// @brief Contains definition of CFG-MSG message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-MSG message fields.
/// @see CfgMsg
struct CfgMsgFields
{
    /// @brief Definition of "id" field (combining class ID and message ID).
    using id = ublox::field::MsgId;

    /// @brief Definition of "rate" field.
    using rate =
        field::common::ListT<
            field::common::U1,
            comms::option::SequenceFixedSize<6>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        id,
        rate
    >;
};

/// @brief Definition of CFG-MSG message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgMsgFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgMsg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields::All>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields::All>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_id, ///< @b id field, see @ref CfgMsgFields::id
        FieldIdx_rate, ///< @b rate field, see @ref CfgMsgFields::rate
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgMsg() = default;

    /// @brief Copy constructor
    CfgMsg(const CfgMsg&) = default;

    /// @brief Move constructor
    CfgMsg(CfgMsg&& other) = default;

    /// @brief Destructor
    virtual ~CfgMsg() = default;

    /// @brief Copy assignment
    CfgMsg& operator=(const CfgMsg&) = default;

    /// @brief Move assignment
    CfgMsg& operator=(CfgMsg&&) = default;
};


}  // namespace message

}  // namespace ublox

