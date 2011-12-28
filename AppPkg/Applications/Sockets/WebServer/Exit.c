/*++
  This file contains an 'Intel UEFI Application' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/
/*++

Copyright (c)  2011 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

--*/

/** @file
  Exit response page

**/

#include <WebServer.h>


/**
  Respond with the Exit page

  @param [in] SocketFD      The socket's file descriptor to add to the list.
  @param [in] pPort         The WSDT_PORT structure address
  @param [out] pbDone       Address to receive the request completion status

  @retval EFI_SUCCESS       The request was successfully processed

**/
EFI_STATUS
ExitPage (
  IN int SocketFD,
  IN WSDT_PORT * pPort,
  OUT BOOLEAN * pbDone
  )
{
  EFI_STATUS Status;
  
  DBG_ENTER ( );
  
  //
  //  Send the Hello World page
  //
  for ( ; ; ) {
    //
    //  Tell the web-server to exit
    //
    mWebServer.bRunning = FALSE;

    //
    //  Send the page header
    //
    Status = HttpPageHeader ( SocketFD, pPort, L"Exit" );
    if ( EFI_ERROR ( Status )) {
      break;
    }
  
    //
    //  Send the page body
    //
    Status = HttpSendAnsiString ( SocketFD,
                                  pPort,
                                  "<h1>Exit</h1>\r\n"
                                  "<p>\r\n"
                                  "  Exiting the web-server application.\r\n"
                                  "</p>\r\n" );
    if ( EFI_ERROR ( Status )) {
      break;
    }
  
    //
    //  Send the page trailer
    //
    Status = HttpPageTrailer ( SocketFD, pPort, pbDone );
    break;
  }
    
  //
  //  Return the operation status
  //
  DBG_EXIT_STATUS ( Status );
  return Status;
}
