//
// C++ Interface: track
//
// Description:
//
//
// Author: Tue Haste Andersen <haste@diku.dk>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TRACK_H
#define TRACK_H

#include <QtCore>
#include <qdom.h>
#include <QMenu>
#include <QObject>
#include <QDropEvent>
#include "trackplaylist.h"
#include "trackplaylistlist.h"

class TrackImporter;
class TrackInfoObject;
class TrackCollection;
class EngineBuffer;
class MixxxView;
class WTrackTable;
class WTrackTableModel;
class WPlaylistListModel;
class WTreeList;
class ControlObjectThreadMain;
class WaveSummary;
class BpmDetector;
class QSortFilterProxyModel;
class QDirModel;
class LibraryScanner;
class LibraryScannerDialog;

// This define sets the version of the tracklist. If any code is changed or
// bugfixed, this number should be increased. If TRACK_VERSION is larger
// than the version written in the current tracklist, the list will be
// re-parsed.
const int TRACK_VERSION = 10;

/**
@author Tue Haste Andersen
*/
class Track : public QObject
{
    Q_OBJECT
public:
    Track(QString location, MixxxView *pView, EngineBuffer *pBuffer1, EngineBuffer *pBuffer2, WaveSummary *pWaveSummary, BpmDetector *pBpmDetector, QString musiclocation);
    ~Track();
    /** Read xml file */
    void readXML(QString location);
    /** Write content to XML file */
    void writeXML(QString location);
    /** Get pointer to TrackCollection */
    TrackCollection *getTrackCollection();
	/** Current active playlist */
    TrackPlaylist *m_pActivePlaylist;
    /** Force an update of playlist menu and anything that sees the playlists*/
    void updatePlaylistViews();
	/**location of new music files*/
	QString musicDir;


public slots:
    /** Decode playlist drops to WTrackTable, and loads corresponding playlist */
    void slotDrop(QDropEvent *e);
    /** Activate a playlist of the given name */
    void slotActivatePlaylist(QString name);
	/**Activate a Playlist from ComboBox*/
	void slotActivatePlaylist(int index);
    /** Add a new playlist */
    void slotNewPlaylist();
    /** Delete a playlist */
    void slotDeletePlaylist(QString qName);
    /** Import a Playlist from a different format */
    void slotImportPlaylist();
    /** Load the given track in player 1 */
    void slotLoadPlayer1(TrackInfoObject *pTrackInfoObject, bool bStartFromEndPos = false);
    /** Load the given track in player 2 */
    void slotLoadPlayer2(TrackInfoObject *pTrackInfoObject, bool bStartFromEndPos = false);
    /** Load the given track in player 1 if it exists */
    void slotLoadPlayer1(QString filename, bool bStartFromEndPos = false);
    /** Load the given track in player 2 if it exists */
    void slotLoadPlayer2(QString filename, bool bStartFromEndPos = false);
    /** Slot used when playback reaches end of track */
    void slotEndOfTrackPlayer1(double);
    /** Slot used when playback reaches end of track */
    void slotEndOfTrackPlayer2(double);
    /** Slot for loading next track in player 1 */
    void slotNextTrackPlayer1(double);
    /** Slot for loading previous track in player 1 */
    void slotPrevTrackPlayer1(double);
    /** Slot for loading next track in player 1 */
    void slotNextTrackPlayer2(double);
    /** Slot for loading previous track in player 1 */
    void slotPrevTrackPlayer2(double);

    /** Slots for loading the selected track into players */
    void slotLoadSelectedTrackCh1(double);
    void slotLoadSelectedTrackCh2(double);
    /** Slots for moving the selection cursor in the track list */
    void slotSelectNextTrack(double);
    void slotSelectPrevTrack(double);

    /** Returns pointer to active playlist */
    TrackPlaylist *getActivePlaylist();
    /** Slot for sending track to Play Queue */
    void slotSendToPlayqueue(TrackInfoObject *pTrackInfoObject);
    /** Slot for sending track to Play Queue */
    void slotSendToPlayqueue(QString filename);
signals:
    /** A new track has been loaded in player 1 */
    void newTrackPlayer1(TrackInfoObject *);
    /** A new track has been loaded in player 2 */
    void newTrackPlayer2(TrackInfoObject *);
    /** Signal to update playlists menu */
    void updateMenu(TrackPlaylistList *);
    /** Signal to set active playlist */
    void activePlaylist(TrackPlaylist *);
private:
    /** Returns pointer to playlist by the given name */
    TrackPlaylist *getPlaylist(QString qName);
    /** Pointer to the Importer class */
    TrackImporter *m_pTrackImporter;
    /** List of pointers to TrackPlaylists */
    TrackPlaylistList m_qPlaylists;
	/** Model for Library information*/
    WTrackTableModel *m_pLibraryModel;
    /**Model for Playqueue information*/
    WTrackTableModel *m_pPlayQueueModel;
    /** Model containing the list of playlists */
    WPlaylistListModel *m_pPlaylistListModel;
    /** Pointer to playlist for which a popup menu is currently displayed */
    TrackPlaylist *m_pActivePopupPlaylist;
    /** Pointer to TrackInfoObject for which a popup menu is currently displayed */
    TrackInfoObject *m_pActivePopupTrack;
    /** Pointer to TrackCollection */
    TrackCollection *m_pTrackCollection;
    /** Pointer to MixxxView */
    MixxxView *m_pView;
    /** Pointer to EngineBuffer for channel 1 and 2 */
    EngineBuffer *m_pBuffer1, *m_pBuffer2;
    /** Pointer to TrackInfoObject's of current loaded tracks */
    TrackInfoObject *m_pTrackPlayer1, *m_pTrackPlayer2;
    /** Pointer to ControlObject signalling end of track */
    ControlObjectThreadMain *m_pEndOfTrackCh1, *m_pEndOfTrackCh2;
    /** Pointer to ControlObject dertermining end of track mode */
    ControlObjectThreadMain *m_pEndOfTrackModeCh1, *m_pEndOfTrackModeCh2;
    /** Pointer to ControlObject for play buttons */
    ControlObjectThreadMain *m_pPlayButtonCh1, *m_pPlayButtonCh2;
    /** Pointer to ControlObject for next/prev buttons */
    ControlObjectThreadMain *m_pNextTrackCh1, *m_pNextTrackCh2, *m_pPrevTrackCh1, *m_pPrevTrackCh2;
    /** Pointer to ControlObject for playlist navigation/loading into Players */
    ControlObjectThreadMain *m_pLoadSelectedTrackCh1, *m_pLoadSelectedTrackCh2, *m_pSelectNextTrack, *m_pSelectPrevTrack;
    /** Pointer to ControlObject for play position */
    ControlObjectThreadMain *m_pPlayPositionCh1, *m_pPlayPositionCh2;
    /** Pointer to waveform summary generator */
    WaveSummary *m_pWaveSummary;
    /** Pointer to BPM detection queue */
    BpmDetector *m_pBpmDetector;
    /** Pointer to the library scanner */
    LibraryScanner *m_pScanner;
    /** Pointer to the library scanning dialog */
    LibraryScannerDialog* m_pLibScannerDlg;
};

#endif
