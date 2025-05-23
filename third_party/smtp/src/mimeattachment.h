/*
  Copyright (c) 2011-2012 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  See the LICENSE file for more details.
*/

#ifndef MIMEATTACHMENT_H
#define MIMEATTACHMENT_H


#include "smtpmime_global.h"
#include "mimepart.h"
#include "mimefile.h"

class SMTP_MIME_EXPORT MimeAttachment : public MimeFile
{
public:

    /* [1] Constructors and Destructors */

    MimeAttachment(QFile* file, const QString& filename = "");
    ~MimeAttachment();

    /* [1] --- */

protected:

    /* [2] Protected methods */
    /* [2] --- */
};

#endif // MIMEATTACHMENT_H
