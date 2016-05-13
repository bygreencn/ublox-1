//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#include "AidEphPollSv.h"

template class ublox::message::AidEphPollSv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidEphPollSv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidEphPollSv>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidEphPollSvFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidEphPollSvFields::svid>().name("svid").asMap());

    assert(props.size() == AidEphPollSv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidEphPollSv::AidEphPollSv() = default;
AidEphPollSv::~AidEphPollSv() = default;

AidEphPollSv& AidEphPollSv::operator=(const AidEphPollSv&) = default;
AidEphPollSv& AidEphPollSv::operator=(AidEphPollSv&&) = default;

const char* AidEphPollSv::nameImpl() const
{
    static const char* Str = "AID-EPH (Poll SV)";
    return Str;
}

const QVariantList& AidEphPollSv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

