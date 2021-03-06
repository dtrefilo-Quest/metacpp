/****************************************************************************
* Copyright 2014-2015 Trefilov Dmitrij                                      *
*                                                                           *
* Licensed under the Apache License, Version 2.0 (the "License");           *
* you may not use this file except in compliance with the License.          *
* You may obtain a copy of the License at                                   *
*                                                                           *
*    http://www.apache.org/licenses/LICENSE-2.0                             *
*                                                                           *
* Unless required by applicable law or agreed to in writing, software       *
* distributed under the License is distributed on an "AS IS" BASIS,         *
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
* See the License for the specific language governing permissions and       *
* limitations under the License.                                            *
****************************************************************************/
#ifndef INITVISITOR_H
#define INITVISITOR_H
#include "config.h"
#include "VisitorBase.h"

namespace metacpp
{

/** \brief Visitor used for initialization of object using common introspection mechanism  */
class InitVisitor :
    public VisitorBase
{
public:
    /** \brief Constructs a new instance of InitVisitor  */
    InitVisitor();
    ~InitVisitor(void);

    /** \brief Overrides metacpp::VisitorBase::visitField  */
    void visitField(Object *obj, const MetaFieldBase *field) override;
};

} // namespace metacpp

#endif // INITVISITOR_H
