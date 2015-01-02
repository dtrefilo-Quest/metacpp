#include "InitVisitor.h"

namespace metacpp
{

pkInitVisitor::pkInitVisitor()
{
}


pkInitVisitor::~pkInitVisitor(void)
{
}

void pkInitVisitor::visitField(Object *obj, const MetaField *field)
{
    if (field->nullable())
    {
        switch (field->type())
        {
        default:
        case eFieldVoid:
            throw std::invalid_argument(std::string("Unknown field type: ") + (char)field->type());
        case eFieldBool:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<bool> >(obj).reset();
            else
                field->access<Nullable<bool> >(obj) =
                        reinterpret_cast<const MetaFieldBool *>(field)->defaultValue();
            break;
        case eFieldInt:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<int32_t> >(obj).reset();
            else
                field->access<Nullable<int32_t> >(obj) =
                        reinterpret_cast<const MetaFieldInt *>(field)->defaultValue();
            break;
        case eFieldUint:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<uint32_t> >(obj).reset();
            else
                field->access<Nullable<uint32_t> >(obj) =
                        reinterpret_cast<const MetaFieldUint *>(field)->defaultValue();
            break;
        case eFieldEnum:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<uint32_t> >(obj).reset();
            else
                field->access<Nullable<uint32_t> >(obj) =
                        reinterpret_cast<const MetaFieldEnum *>(field)->defaultValue();
            break;
        case eFieldFloat:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<float> >(obj).reset();
            else
                field->access<Nullable<float> >(obj) =
                        reinterpret_cast<const MetaFieldFloat *>(field)->defaultValue();
            break;
        case eFieldDouble:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<double> >(obj).reset();
            else
                field->access<Nullable<double> >(obj) = reinterpret_cast<const MetaFieldDouble *>(field)->defaultValue();
        case eFieldDateTime:
            if (eOptional == field->mandatoriness())
                field->access<Nullable<DateTime> >(obj).reset();
            else
                field->access<Nullable<DateTime> >(obj) = DateTime(0);
            break;
        }
        return;
    }

    switch (field->type())
	{
	default:
	case eFieldVoid:
        throw std::invalid_argument(std::string("Unknown field type: ") + (char)field->type());
    case eFieldBool:
        field->access<bool>(obj) = reinterpret_cast<const MetaFieldBool *>(field)->defaultValue();
		break;
    case eFieldInt:
        field->access<int32_t>(obj) = reinterpret_cast<const MetaFieldInt *>(field)->defaultValue();
		break;
	case eFieldUint:
        field->access<uint32_t>(obj) = reinterpret_cast<const MetaFieldUint *>(field)->defaultValue();
		break;
    case eFieldFloat:
        field->access<float>(obj) = reinterpret_cast<const MetaFieldFloat *>(field)->defaultValue();
		break;
    case eFieldDouble:
        field->access<double>(obj) = reinterpret_cast<const MetaFieldDouble *>(field)->defaultValue();
        break;
    case eFieldString:
        field->access<metacpp::String>(obj) = reinterpret_cast<const MetaFieldString *>(field)->defaultValue();
		break;
    case eFieldEnum:
        field->access<uint32_t>(obj) = reinterpret_cast<const MetaFieldEnum *>(field)->defaultValue();
		break;
    case eFieldArray:
        field->access<metacpp::Array<char> >(obj).clear();
		break;
    case eFieldObject: {
        field->access<Object>(obj).init();
		break;
    case eFieldDateTime:
        field->access<DateTime>(obj) = DateTime(0);
        break;
    }
    }
}

} // namespace metacpp
