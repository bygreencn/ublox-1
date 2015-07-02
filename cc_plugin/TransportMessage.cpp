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

#include "TransportMessage.h"

#include <cassert>

#include <QtCore/QVariantMap>

#include "cc_plugin/field/MsgId.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace
{

QVariantMap createSync1MemberData()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "SYNC 1");
    return map;
}

QVariantMap createSync2MemberData()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "SYNC 2");
    return map;
}

QVariantMap createLengthProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "LENGTH");
    return map;
}

QVariantMap createPayloadProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "PAYLOAD");
    return map;
}

QVariantMap createChecksumProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "CK");
    return map;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createSync1MemberData());
    props.append(createSync2MemberData());
    props.append(field::msgIdProperties());
    props.append(createLengthProperties());
    props.append(createPayloadProperties());
    props.append(createChecksumProperties());
    assert(props.size() == TransportMessage::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const QVariantList& TransportMessage::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

comms::ErrorStatus TransportMessage::readImpl(ReadIterator& iter, std::size_t size)
{
    static const auto ChecksumLen =
        sizeof(ublox::ChecksumField<cc_plugin::Stack::Message::Field>::ValueType);

    size -= ChecksumLen;
    auto es = Base::readFieldsUntil<FieldIdx_Checksum>(iter, size);
    if (es == comms::ErrorStatus::Success) {
        size += ChecksumLen;
        es = readFieldsFrom<FieldIdx_Checksum>(iter, size);
    }
    return es;
}


}  // namespace cc_plugin

}  // namespace ublox

